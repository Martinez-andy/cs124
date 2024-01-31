#include <iostream>
#include <stdio.h>
#include <chrono>
#include "/Users/andymartinez/eigen-3.4.0/Eigen/Dense"
#include <utility>
#include <string>

template<typename Function, typename... Args>
std::pair<long long, decltype(std::declval<Function>()(std::declval<Args>()...))>
timeFunction(Function&& func, Args&&... args);
long long recFib(int n);
long long iterFib(int n);
long long matrixFib(int n);
Eigen::Matrix2d repeatedSquare(Eigen::Matrix2d matrix, int pow);

int main() {
    int fib;
    printf("Fib Number: ");
    std::cin >> fib;


    auto iterative = timeFunction(iterFib, fib);
    auto recursive = timeFunction(recFib, fib);
    auto matrix = timeFunction(matrixFib, fib);
    
    printf("Recursive time: %lld, %lld\n", recursive.first, recursive.second);
    printf("Iterative time: %lld, %lld\n", iterative.first, iterative.second);
    printf("Matrix time: %lld, %lld\n", matrix.first, matrix.second);

    return 0;
}

template<typename Function, typename... Args>
std::pair<long long, decltype(std::declval<Function>()(std::declval<Args>()...))>
timeFunction(Function&& func, Args&&... args) {
    // Open namespaces for chrono, makes for cleaner code.
    using namespace std::chrono; 

    // Start timer 
    auto start = high_resolution_clock::now(); 

    // Call function on provided input
    auto res = std::forward<Function>(func)(std::forward<Args>(args)...); 

    // End timer
    auto end = high_resolution_clock::now();

    auto timeTaken = duration_cast<microseconds>(end - start).count(); 

    // Calculate and return time it took function to execute.
    return std::make_pair(timeTaken, res);
}

long long recFib(int n) {
    if (n <= 1) 
        return n;
    return recFib(n - 1) + recFib(n - 2);
}

long long iterFib(int n) {
    long long A[n + 1];

    // Slides say A[0] == 1 but I think it should be 0?
    A[0] = 0;
    A[1] = 1;

    for (int i = 2; i < n + 1; i++)
        A[i] = A[i - 1] + A[i - 2];

    return A[n];
}

long long matrixFib(int n) {
    Eigen::Matrix2d matrix;
    Eigen::Vector2d init;
    init << 1, 0;

    matrix << 1, 1,
              1, 0;

    Eigen::Matrix2d result = repeatedSquare(matrix, n - 1);

    Eigen::Vector2d res = result * init;
    return std::round(res[0]);
}

Eigen::Matrix2d repeatedSquare(Eigen::Matrix2d matrix, int pow) {
    Eigen::Matrix2d result = Eigen::Matrix2d::Identity();
    Eigen::Matrix2d base = matrix;

    while (pow > 0) {
        if (pow % 2 == 1) {
            result *= base;
        }
        base *= base;
        pow /= 2;
    }

    return result;
}