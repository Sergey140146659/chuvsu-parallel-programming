#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <format>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi = 0, size_mpi = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    long long N;
    if (rank_mpi == 0) {
        std::cin >> N;
    }
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long double local_pi = 0;

    #pragma omp parallel reduction(+:local_pi)
    {
        #pragma omp for schedule(static)
        for (long long i = rank_mpi; i < N; i += size_mpi) {
            long double x_i = (i + 0.5) / static_cast<long double> (N);
            local_pi += 4 / ((1 + x_i * x_i) * static_cast<long double> (N));
        }
    }

    long double pi = 0.0;
    MPI_Reduce(&local_pi, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank_mpi == 0) {
        std::cout << std::format("{}\n", pi);
    }

    MPI_Finalize();
    return 0;
}
