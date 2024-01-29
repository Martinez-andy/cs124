#include <iostream>
#include <stdio.h>
#include <chrono>
#include <Eigen/Dense>

template<typename Function, typename... Args>
long long timeFunction(Function&& func, Args&&... args);
int recFib(int n);
int iterFib(int n);
int matrixFib(int n);


int main() {
    int fib;
    printf("Fib Number: \n");
    std::cin >> fib;
    
    printf("Fib num: %i\n", matrixFib(fib));
    /*
    printf("Recursive time: %lld\n", timeFunction(recFib, fib));
    printf("Iterative time: %lld\n", timeFunction(iterFib, fib));
    printf("Matrix time: %lld\n", timeFunction(matrixFib, fib));
    */
    return 0;
}

template<typename Function, typename... Args>
long long timeFunction(Function&& func, Args&&... args) {
    // Open namespaces for chrono, makes for cleaner code.
    using namespace std::chrono; 

    // Start timer 
    auto start = high_resolution_clock::now(); 

    // Call function on provided input
    std::forward<Function>(func)(std::forward<Args>(args)...); 

    // End timer
    auto end = high_resolution_clock::now();

    // Calculate and return time it took function to execute.
    return duration_cast<microseconds>(end - start).count(); 
}

int recFib(int n) {
    if (n <= 1) 
        return n;
    return recFib(n - 1) + recFib(n - 2);
}

int iterFib(int n) {
    int A[n + 1];

    // Slides say A[0] == 1 but I think it should be 0?
    A[0] = 0;
    A[1] = 1;

    for (int i = 2; i < n + 1; i++)
        A[i] = A[i - 1] + A[i - 2];

    return A[n];
}

int matrixFib(int n) {
    return n;
}