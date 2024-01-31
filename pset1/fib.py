import numpy as np
import time

def main():
    fib = int(input("Fib number: "))
    
    iter = timeFunc(iterFib, fib)
    # rec = timeFunc(recFib, fib)
    mat = timeFunc(matrixFib, fib)
    
    print(f"Iterative time: {iter[0]}, {iter[1]}")
    # print(f"Recursive time: {rec[0]}, {rec[1]}")
    print(f"Matix time: {mat[0]}, {mat[1]}")
    
    return 0

def recFib(n: int):
    if n <= 1:
        return n
    return recFib(n - 1) + recFib(n - 2)

def matrixFib(n: int):
    fibMat = np.array([[1, 1], 
                       [1, 0]])
    fibMat = np.linalg.matrix_power(fibMat, n - 1)
    init = np.array([1, 0])
    return fibMat.dot(init)[0]

def iterFib(n: int):
    A = [0, 1]
    for i in range(2, n + 1):
        A.append(A[i - 1] + A[i - 2])
    return A[n]

def timeFunc(func, arg):
    start = time.time()
    res = func(arg)
    end = time.time()
    return (end - start), res

main()