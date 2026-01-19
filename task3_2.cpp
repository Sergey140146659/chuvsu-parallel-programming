#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    std::cin >> k;
    #pragma omp parallel num_threads(k)
    {
        int tid = omp_get_thread_num();
        int T  = omp_get_num_threads();
        if (tid % 2 == 0) {
            #pragma omp critical
            std::cout << std::format("I am thread {} from {} threads\n", tid, T);
        }
    }
}
