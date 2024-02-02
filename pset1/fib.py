import numpy as np
import time
import sys

modVal = 2 ** 16

def main():
    print("Running program")
    
    fib = 2 ** 1000000
    
    # rec = timeFunc(recFib, fib)
    # iter = timeFunc(iterFib, fib)
    mat = timeFunc(matrixFib, fib)
    
    # print(f"Recursive time: {rec[0]}")
    # print(f"Iterative time: {iter[0]}")
    print(f"Matix time: {mat[0]}")
    
    return 0

def recFib(n: int):
    if n <= 1:
        return n % modVal
    return (recFib(n - 1) % modVal) + (recFib(n - 2) % modVal)

def matrixFib(n: int):
    fibMat = np.array([[1, 1], 
                       [1, 0]])
    fibMat = np.linalg.matrix_power(fibMat, n - 1)
    init = np.array([1, 0])
    return fibMat.dot(init)[0]

def iterFib(n: int):
    A = [0, 1]
    for i in range(2, n + 1):
        A.append((A[i - 1] + A[i - 2]) % modVal)
    return A[n]

def timeFunc(func, arg):
    start = time.time()
    res = func(arg)
    end = time.time()
    return (end - start), res

def T(n: int):
    if n == 1:
        return 1

    return T(n - 1) + (n ** 2) - n

vals = []
for i in range(1, 100):
    vals.append(T(i))
    if i > 1:
        print(vals[i - 1] / vals[i - 2])
print(vals)