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

    if (rank == 0) {
        for (int i = 0; i < rows_per_proc * n; ++i) {
            a_local[i] = a[i];
        }

        for (int p = 1; p < size; ++p) {
            MPI_Send(
                a.data() + p * rows_per_proc * n,
                rows_per_proc * n,
                MPI_DOUBLE,
                p,
                0,
                MPI_COMM_WORLD
            );
        }
    } else {
        MPI_Recv(
            a_local.data(),
            rows_per_proc * n,
            MPI_DOUBLE,
            0,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );
    }

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


    if (rank == 0) {
        for (int i = 0; i < rows_per_proc * n; ++i) {
            c[i] = c_local[i];
        }

        for (int p = 1; p < size; ++p) {
            MPI_Recv(
                c.data() + p * rows_per_proc * n,
                rows_per_proc * n,
                MPI_DOUBLE,
                p,
                0,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );
        }
    } else {
        MPI_Send(
            c_local.data(),
            rows_per_proc * n,
            MPI_DOUBLE,
            0,
            0,
            MPI_COMM_WORLD
        );
    }


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
