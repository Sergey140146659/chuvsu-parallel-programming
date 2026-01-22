#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    long long N;
    std::cin >> k >> N;
    long long sum = 0;
    #pragma omp parallel num_threads(k)
    {
        int rank = omp_get_thread_num();
        long long current_sum = 0;

        #pragma omp for
        for (long long i = 1; i <= N; ++i) {
            current_sum += i;
        }
        #pragma omp atomic
        sum += current_sum;

        #pragma omp critical
        std::cout << std::format("[{}]: Sum = {}\n", rank, current_sum);
    }

    std::cout << std::format("Sum = {}\n", sum);
}
