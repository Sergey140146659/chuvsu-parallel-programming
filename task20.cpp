#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int send = 45;
        MPI_Request req;
        MPI_Status status;

        MPI_Isend(&send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, &status);

        std::cout << "process 0 send message with number: " << send << "\n";
    } else if (rank == 1) {
        int receive = 0;
        MPI_Request req;
        MPI_Status status;

        MPI_Irecv(&receive, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, &status);

        std::cout << "process 1 receive message with number: " << receive << "\n";
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
