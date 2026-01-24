#include <iostream>
#include <vector>
#include <format>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    std::vector<char> s;

    if (rank == 0) {
        std::cin >> n;
        s.resize(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> s[i];
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        s.resize(n);
    }
    MPI_Bcast(s.data(), n, MPI_CHAR, 0, MPI_COMM_WORLD);

    std::vector<int> local(26, 0);
    for (int i = rank; i < n; i += size) {
        local[s[i] - 'a']++;
    }

    std::vector<int> global(26, 0);
    MPI_Reduce(local.data(), global.data(), 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < 26; ++i) {
            if (global[i] > 0) {
                char c = static_cast<char>('a' + i);
                std::cout << std::format("{} = {}\n", c, global[i]);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
