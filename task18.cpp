#include <iostream>
#include <format>
#include <mpi.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int send = 0;
        MPI_Send(&send, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

        int receive;
        MPI_Status status;
        MPI_Recv(&receive, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);

        std::cout << std::format("[{}]: receive message '{}'\n", rank, receive);
    } else {
        int receive;
        MPI_Status status;
        MPI_Recv(&receive, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << std::format("[{}]: receive message '{}'\n", rank, receive);
        ++receive;

        MPI_Send(&receive, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
