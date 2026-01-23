#include <iostream>
#include <vector>
#include <format>
#include <omp.h>

int main() {
    std::vector<long long> Ns = {100LL, 10'000'000LL, 4'000'000'000LL};
    std::vector<int> threads_list = {1, 2, 4, 6, 8, 10, 12};

    std::cout << std::format("{:<15} {:<10} {:<12} {:<18}\n",
                             "N", "threads", "time_sec", "pi");

    for (long long N : Ns) {
        for (int k : threads_list) {

            long double pi = 0.0L;

            double start = omp_get_wtime();

            #pragma omp parallel num_threads(k)
            {
                long double local = 0.0L;

                #pragma omp for schedule(static, 1)
                for (long long i = 0; i < N; ++i) {
                    long double x = ((long double)i + 0.5L) / (long double)N;
                    local += 4.0L / ((1.0L + x * x) * (long double)N);
                }

                #pragma omp critical
                {
                    pi += local;
                }
            }

            double end = omp_get_wtime();

            std::cout << std::format("{:<15} {:<10} {:<12.6f} {:.15f}\n",
                                     N, k, (end - start), (double)pi);
        }
    }

    return 0;
}
