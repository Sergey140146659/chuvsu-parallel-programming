#include <iomanip>
#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n;
    if (rank == 0) {
        std::cin >> n;
    }

    MPI_Bcast(&n, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();

    long double local = 0.0;
    for (long long i = rank; i < n; i += size) {
        long double x = (i + 0.5) / static_cast<long double> (n);
        local += 4.0 / ((1.0 + x * x) * static_cast<long double> (n));
    }

    long double global = 0.0;

    if (rank == 0) {
        global = local;
        for (int src = 1; src < size; ++src) {
            long double tmp = 0.0;
            MPI_Recv(&tmp, 1, MPI_LONG_DOUBLE, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global += tmp;
        }
    } else {
        MPI_Send(&local, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double t1 = MPI_Wtime();

    if (rank == 0) {
        std::cout << std::fixed << std::setprecision(10) << global << "\n";
        std::cout << "time_sec " << std::fixed << std::setprecision(6) << (t1 - t0) << "\n";
    }

    MPI_Finalize();
    return 0;
}
