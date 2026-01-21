#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    long long N;
    std::cin >> k >> N;
    k = 4, N = 10;
    long long sum = 0;
    //[<Номер нити>]: calculation of the iteration number <Номер итерации>.
    #pragma omp parallel num_threads(k) reduction(+:sum)
    {
        int rank = omp_get_thread_num();
        long long current_sum = 0;

        #pragma omp for schedule(static, 2)
        for (long long i = 1; i <= N; ++i) {
            current_sum += i;

            #pragma omp critical
            std::cout << std::format("thread [{}]: calculation of the iteration number <{}>\n", rank, i);
        }
        sum += current_sum;

        #pragma omp critical
        std::cout << std::format("[{}]: Sum = {}\n", rank, current_sum);
    }


    std::cout << std::format("Sum = {}", sum);
}
