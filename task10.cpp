#include <iostream>
#include <format>
#include <omp.h>

int main() {
    int k;
    std::cin >> k;

    #pragma omp parallel num_threads(k)
    {
        int rank = omp_get_thread_num();

        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma omp critical
                std::cout << std::format("[{}]: came in section 1\n", rank);
            }

            #pragma omp section
            {
                #pragma omp critical
                std::cout << std::format("[{}]: came in section 2\n", rank);
            }

            #pragma omp section
            {
                #pragma omp critical
                std::cout << std::format("[{}]: came in section 3\n", rank);
            }
        }

        #pragma omp critical
        std::cout << std::format("[{}]: parallel region\n", rank);
    }
}
