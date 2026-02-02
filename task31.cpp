#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <format>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi, size_mpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    int n;
    if (rank_mpi == 0) {
        std::cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    omp_set_num_threads(n);

    #pragma omp parallel
    {
        int rank_omp = omp_get_thread_num();
        int size_omp = omp_get_num_threads();

        std::cout << std::format(
            "I am {} thread from {} process. Number of hybrid threads = {}.\n",
            rank_omp, rank_mpi, size_omp * size_mpi
        );
    }

    MPI_Finalize();
    return 0;
}
