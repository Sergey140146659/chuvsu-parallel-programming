#include <mpi.h>
#include <iostream>
#include <vector>
#include <iomanip>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = 0;
    if (rank == 0) {
        std::cin >> n;
    }

    MPI_Bcast(&n, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long double local = 0.0;
    for (long long i = rank; i < n; i += size) {
        long double x_i = (i + 0.5) / static_cast<long double>(n);
        local += 4 / ((1 + x_i * x_i) * static_cast<long double>(n));
    }


    std::vector<long double> sums;
    if (rank == 0) {
        sums.resize(size, 0.0);
    }

    MPI_Win win;
    if (rank == 0) {
        MPI_Win_create(
            sums.data(),
            static_cast<MPI_Aint>(size * sizeof(long double)),
            static_cast<int>(sizeof(long double)),
            MPI_INFO_NULL,
            MPI_COMM_WORLD,
            &win
        );
    } else {
        MPI_Win_create(
            nullptr,
            0,
            static_cast<int>(sizeof(long double)),
            MPI_INFO_NULL,
            MPI_COMM_WORLD,
            &win
        );
    }

    MPI_Win_fence(0, win);

    MPI_Put(
        &local, 1, MPI_LONG_DOUBLE,
        0, rank, 1, MPI_LONG_DOUBLE,
        win
    );

    MPI_Win_fence(0, win);

    if (rank == 0) {
        long double pi = 0.0;
        for (int r = 0; r < size; ++r) {
            pi += sums[r];
        }
        std::cout << std::fixed << std::setprecision(8) << pi << "\n";
    }

    MPI_Win_free(&win);
    MPI_Finalize();
    return 0;
}
