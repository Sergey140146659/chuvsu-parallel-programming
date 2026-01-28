#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include <format>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> even_ranks;
    for (int r = 0; r < size; r += 2) {
        even_ranks.emplace_back(r);
    }

    MPI_Group oldgroup, group;
    MPI_Comm_group(MPI_COMM_WORLD, &oldgroup);
    MPI_Group_incl(oldgroup,
                   static_cast<int>(even_ranks.size()),
                   even_ranks.data(),
                   &group);

    MPI_Comm newcomm;
    MPI_Comm_create(MPI_COMM_WORLD, group, &newcomm);

    int newrank = -1, newsize = 0;
    if (newcomm != MPI_COMM_NULL) {
        MPI_Comm_rank(newcomm, &newrank);
        MPI_Comm_size(newcomm, &newsize);
    }

    std::string message;
    int len = 0;

    if (newcomm != MPI_COMM_NULL) {
        if (newrank == 0) {
            std::cin >> message;
            len = static_cast<int>(message.size());
        }

        MPI_Bcast(&len, 1, MPI_INT, 0, newcomm);
        message.resize(len);
        MPI_Bcast(message.data(), len, MPI_CHAR, 0, newcomm);
    }

    std::cout << std::format(
        "MPI_COMM_WORLD: {} from {}.\nNew comm: {} from {}.\nMessage = {}\n\n",
        rank,
        size,
        newrank,
        newsize,
        (newcomm != MPI_COMM_NULL ? message : "no")
    );

    MPI_Group_free(&group);
    MPI_Group_free(&oldgroup);
    if (newcomm != MPI_COMM_NULL) {
        MPI_Comm_free(&newcomm);
    }

    MPI_Finalize();
    return 0;
}
