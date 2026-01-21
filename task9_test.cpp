#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

int main() {
    int N;
    std::cin >> N;

    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(-100, 100);

    std::vector<std::vector<int>> a(N, std::vector<int>(N));
    std::vector<std::vector<int>> b(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            a[i][j] = dist(rng);
            b[i][j] = dist(rng);
        }

    std::vector<std::vector<long long>> C1(N, std::vector<long long>(N, 0));
    std::vector<std::vector<long long>> C2(N, std::vector<long long>(N, 0));

    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            long long s = 0;
            for (int k = 0; k < N; ++k) s += 1LL * a[i][k] * b[k][j];
            C1[i][j] = s;
        }
    auto t2 = std::chrono::steady_clock::now();
    double serial_sec = std::chrono::duration<double>(t2 - t1).count();

    auto t3 = std::chrono::steady_clock::now();
    #pragma omp parallel for num_threads(5) schedule(static)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            long long s = 0;
            for (int k = 0; k < N; ++k) s += 1LL * a[i][k] * b[k][j];
            C2[i][j] = s;
        }
    auto t4 = std::chrono::steady_clock::now();
    double parallel_sec = std::chrono::duration<double>(t4 - t3).count();

    bool ok = true;
    for (int i = 0; i < N && ok; ++i){
        for (int j = 0; j < N; ++j){
            if (C1[i][j] != C2[i][j]) {
                ok = false; break;
            }
        }
    }


    std::cout << "serial: " << serial_sec << " sec\n";
    std::cout << "parallel: " << parallel_sec << " sec\n";
    std::cout << (ok ? "OK\n" : "NOT OK\n");
}
