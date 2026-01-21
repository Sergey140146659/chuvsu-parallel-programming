#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int N;
    std::cin >> N;
    long double pi = 0;
    #pragma omp parallel num_threads(5) reduction(+:pi)
    {
        int rank = omp_get_thread_num();
        long double current_pi_sum = 0;

        #pragma omp for schedule(static, 1)
        for (long long i = 0; i < N; ++i) {
            long double x_i = (i + 0.5) / static_cast<long double> (N);
            current_pi_sum += 4 / ((1 + x_i * x_i) * static_cast<long double> (N));
        }
        pi += current_pi_sum;

        #pragma omp critical
        std::cout << std::format("[{}]: Part of pi = {}\n", rank, current_pi_sum);
    }


    std::cout << std::format("Pi = {}", pi);
}
