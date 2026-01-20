#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    std::cin >> k;
    #pragma omp parallel num_threads(k)
    {
        int rank = omp_get_thread_num(); // rank должна быть приватной, чтобы не было гонки данных
        #pragma omp critical
        std::cout << std::format("I am thread {} from\n", rank);
    }
}
