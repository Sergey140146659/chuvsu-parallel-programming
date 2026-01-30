#include <iostream>
#include <vector>
#include <format>
#include <iomanip>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<long long> Ns = {100, 10'000'000, 4'000'000'000};

    if (rank == 0) {
        std::cout << std::format("{:<15} {:<10} {:<12} {:<18}\n",
                                 "N", "processes", "time_sec", "pi");
    }

    for (long long N : Ns) {
        MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);
        double start = MPI_Wtime();

        long double local = 0.0;
        for (long long i = rank; i < N; i += size) {
            long double x = (static_cast<long double>(i) + 0.5) / static_cast<long double>(N);
            local += 4.0 / ((1.0 + x * x) * static_cast<long double>(N));
        }

        long double pi = 0.0;
        MPI_Reduce(&local, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);
        double end = MPI_Wtime();

        if (rank == 0) {
            std::cout << std::format("{:<15} {:<10} {:<12.6f} {:.15f}\n", N, size, (end - start), pi);
        }
    }

    MPI_Finalize();
    return 0;
}
