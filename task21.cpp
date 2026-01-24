#include <iostream>
#include <format>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send = rank;
    int receive;

    int to = (rank + 1) % size;
    int from = (rank - 1 + size) % size;
    MPI_Status status;
    MPI_Sendrecv(
        &send, 1, MPI_INT, to, 0,
        &receive, 1, MPI_INT, from, 0,
        MPI_COMM_WORLD, &status
    );

    std::cout << std::format("[{}]: receive message '{}'\n", rank, receive);

    MPI_Finalize();
    return 0;
}
