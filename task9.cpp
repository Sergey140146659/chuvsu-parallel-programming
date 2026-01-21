#include <iostream>
#include <format>
#include <vector>
#include <omp.h>

int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> a(N, std::vector<int> (N));
    std::vector<std::vector<int>> b(N, std::vector<int> (N));
    std::vector<std::vector<int>> c(N, std::vector<int> (N));
    for (auto& row : a) {
        for (int& num : row) {
            std::cin >> num;
        }
    }
    for (auto& row : b) {
        for (int& num : row) {
            std::cin >> num;
        }
    }
    #pragma omp parallel for num_threads(5) schedule(static)
    for (int row = 0; row < N;++row) {
        for (int col = 0; col < N; ++col) {
            int c_el = 0;
            for (int i = 0;i < N;++i){
                c_el += a[row][i] * b[i][col];
            }
            c[row][col] = c_el;
        }
    }
    for (auto& row : c) {
        for (int& num : row) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}
