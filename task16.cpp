#include <iostream>
#include <format>
#include <mpi.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cout << size << " processes.\n";
    } else {
        std::string number = (rank & 1) ? "FIRST!" : "SECOND!";
        std::cout << std::format("I am {} process: {}\n", rank, number);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
