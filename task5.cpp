#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    long long N;
    std::cin >> k >> N;
    long long sum = 0;
    #pragma omp parallel num_threads(k) reduction(+:sum)
    {
        int rank = omp_get_thread_num();
        long long current_sum = 0;
        for (long long i = rank; i <= N; i += k) {
            current_sum += i;
        }
        sum += current_sum;
        std::cout << std::format("[{}]: Sum = {}\n", rank, current_sum);
    }
    std::cout << std::format("Sum = {}", sum);
}
