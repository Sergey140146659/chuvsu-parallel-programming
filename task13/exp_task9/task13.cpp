#include <iostream>
#include <vector>
#include <random>
#include <omp.h>
#include <format>

int main() {
    std::vector<int> Ns = {10, 1000};
    std::vector<int> threads_list = {1, 2, 4, 6, 8, 10, 12};

    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(-100, 100);

    std::cout << std::format("{:<10} {:<10} {:<12}\n",
                             "N", "threads", "time_sec");

    for (int N : Ns) {
        std::vector<std::vector<int>> a(N, std::vector<int>(N));
        std::vector<std::vector<int>> b(N, std::vector<int>(N));
        std::vector<std::vector<int>> c(N, std::vector<int>(N));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = dist(rng);
                b[i][j] = dist(rng);
            }
        }

        for (int k : threads_list) {

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    c[i][j] = 0;
                }
            }

            double start = omp_get_wtime();

            #pragma omp parallel for num_threads(k) schedule(static)
            for (int row = 0; row < N; ++row) {
                for (int col = 0; col < N; ++col) {
                    int sum = 0;
                    for (int t = 0; t < N; ++t) {
                        sum += a[row][t] * b[t][col];
                    }
                    c[row][col] = sum;
                }
            }

            double end = omp_get_wtime();

            std::cout << std::format("{:<10} {:<10} {:<12.6f}\n",
                                     N, k, (end - start));
        }
    }

    return 0;
}
