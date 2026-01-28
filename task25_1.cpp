#include <iostream>
#include <vector>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    std::vector<double> a, b, c;

    if (rank == 0) {
        std::cin >> n;

        a.resize(n * n);
        b.resize(n * n);
        c.resize(n * n);

        for (int i = 0; i < n * n; ++i) {
            std::cin >> a[i];
        }

        for (int i = 0; i < n * n; ++i) {
            std::cin >> b[i];
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = n / size;

    std::vector<double> a_local(rows_per_proc * n);
    std::vector<double> c_local(rows_per_proc * n);

    MPI_Scatter(
        a.data(),
        rows_per_proc * n,
        MPI_DOUBLE,
        a_local.data(),
        rows_per_proc * n,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    if (rank != 0) {
        b.resize(n * n);
    }

    MPI_Bcast(b.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_proc; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += a_local[i * n + k] * b[k * n + j];
            }
            c_local[i * n + j] = sum;
        }
    }

    MPI_Gather(
        c_local.data(),
        rows_per_proc * n,
        MPI_DOUBLE,
        c.data(),
        rows_per_proc * n,
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << c[i * n + j] << " ";
            }
            std::cout << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}
