# ChuvSU Parallel Programming

Репозиторий для заданий по параллельному программированию.

## Сборка task2.cpp

Для сборки и запуска `task2.cpp` используйте следующие команды:

```bash
g++-15 -std=c++17 -fopenmp task2.cpp -o task2
./task2
```

## Сборка task3_1.cpp

Для сборки и запуска `task3_1.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task3_1.cpp -o task3_1
./task3_1
```

## Сборка task3_2.cpp

Для сборки и запуска `task3_2.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task3_2.cpp -o task3_2
./task3_2
```

## Сборка task4.cpp

Для сборки и запуска `task4.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task4.cpp -o task4
./task4
```

## Сборка task5.cpp

Для сборки и запуска `task5.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task5.cpp -o task5
./task5
```

**Пример выполнения:**

Input:
```
10
1000
```

Output:
```
[1]: Sum = 49600
[9]: Sum = 50400
[4]: Sum = 49900
[6]: Sum = 50100
[3]: Sum = 49800
[2]: Sum = 49700
[8]: Sum = 50300
[0]: Sum = 50500
[7]: Sum = 50200
[5]: Sum = 50000
Sum = 500500
```

## Сборка task6.cpp

Для сборки и запуска `task6.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task6.cpp -o task6
./task6
```

**Пример выполнения:**

Input:
```
10
1000
```

Output:
```
[6]: Sum = 65050
[1]: Sum = 15050
[2]: Sum = 25050
[4]: Sum = 45050
[3]: Sum = 35050
[5]: Sum = 55050
[7]: Sum = 75050
[0]: Sum = 5050
[8]: Sum = 85050
[9]: Sum = 95050
Sum = 500500
```

## Сборка task7.cpp

Для сборки и запуска `task7.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task7.cpp -o task7
./task7
```

**Пример выполнения (schedule(static, 2)):**

Input:
```
4
10
```

Output:
```
thread [1]: calculation of the iteration number <3>
thread [1]: calculation of the iteration number <4>
thread [2]: calculation of the iteration number <5>
thread [2]: calculation of the iteration number <6>
thread [3]: calculation of the iteration number <7>
thread [3]: calculation of the iteration number <8>
thread [0]: calculation of the iteration number <1>
thread [0]: calculation of the iteration number <2>
thread [0]: calculation of the iteration number <9>
thread [0]: calculation of the iteration number <10>
[1]: Sum = 7
[0]: Sum = 22
[2]: Sum = 11
[3]: Sum = 15
Sum = 55
```

**Распределение итераций по потокам для разных типов schedule:**

| Номер итерации | static | static, 1 | static, 2 | dynamic | dynamic, 2 | guided | guided, 2 |
|---------------:|-------:|----------:|----------:|--------:|-----------:|-------:|----------:|
| 1  | 0 | 0 | 0 | 2 | 1 | 1 | 2 |
| 2  | 0 | 1 | 0 | 1 | 1 | 1 | 2 |
| 3  | 0 | 2 | 1 | 0 | 0 | 1 | 2 |
| 4  | 1 | 3 | 1 | 3 | 0 | 0 | 0 |
| 5  | 1 | 0 | 2 | 2 | 2 | 0 | 0 |
| 6  | 1 | 1 | 2 | 2 | 2 | 2 | 1 |
| 7  | 2 | 2 | 3 | 2 | 3 | 2 | 1 |
| 8  | 2 | 3 | 3 | 2 | 3 | 3 | 3 |
| 9  | 3 | 0 | 0 | 0 | 1 | 1 | 3 |
| 10 | 3 | 1 | 0 | 0 | 1 | 1 | 2 |

## Сборка task8.cpp

Для сборки и запуска `task8.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task8.cpp -o task8
./task8
```

**Пример выполнения:**

Input:
```
1000000
```

Output:
```
[3]: Part of pi = 0.628318130718177
[1]: Part of pi = 0.6283189307181617
[2]: Part of pi = 0.6283185307183825
[0]: Part of pi = 0.6283193307175647
[4]: Part of pi = 0.6283177307175769
Pi = 3.1415926535898633
```

## Сборка task9.cpp

Для сборки и запуска `task9.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task9.cpp -o task9
./task9
```

**Пример выполнения:**

Input:
```
2
1 3
4 8
5 4
3 0
```

Output:
```
14 4
44 16
```

## Сборка task9_test.cpp (сравнение скорости умножения матриц: без/с распараллеливанием циклов)

Для сборки и запуска `task9_test.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task9_test.cpp -o task9_test
./task9_test
```

**Пример выполнения:**

Input:
```
1000
```

Output:
```
serial: 8.88607 sec
parallel: 1.91855 sec
OK
```

## Сборка task10.cpp

Для сборки и запуска `task10.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task10.cpp -o task10
./task10
```

**Примеры выполнения:**

Input: `2`
```
[0]: came in section 1
[0]: came in section 3
[1]: came in section 2
[0]: parallel region
[1]: parallel region
```

Input: `3`
```
[1]: came in section 1
[0]: came in section 2
[2]: came in section 3
[1]: parallel region
[0]: parallel region
[2]: parallel region
```

Input: `4`
```
[2]: came in section 1
[1]: came in section 2
[0]: came in section 3
[1]: parallel region
[0]: parallel region
[2]: parallel region
[3]: parallel region
```

## Сборка task11.cpp

Для сборки и запуска `task11.cpp` используйте следующие команды:

```bash
g++-15 -std=c++20 -fopenmp task11.cpp -o task11
./task11
```

**Пример выполнения:**

Input:
```
10
1000
```

Output:
```
[2]: Sum = 25050
[3]: Sum = 35050
[1]: Sum = 15050
[5]: Sum = 55050
[6]: Sum = 65050
[4]: Sum = 45050
[7]: Sum = 75050
[8]: Sum = 85050
[0]: Sum = 5050
[9]: Sum = 95050
Sum = 500500
```
