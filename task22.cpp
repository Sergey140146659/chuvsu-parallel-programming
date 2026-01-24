#include <iostream>
#include <format>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send = rank;

    for (int step = 1; step < size; ++step) {
        int to = (rank + step) % size;
        int from = (rank - step + size) % size;

        int receive;

        MPI_Sendrecv(
            &send, 1, MPI_INT, to,   0,
            &receive, 1, MPI_INT, from, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE
        );

        std::cout << std::format("[{}]: receive message '{}' from {}\n", rank, receive, from);
    }

    MPI_Finalize();
    return 0;
}
