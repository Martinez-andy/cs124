import random
import heapq
import sys


# Takes in sequence A and returns A' (used for pre-partitioned algs)
def prepart(A):
    # Initialize A to be list of zeros
    A_prime = [0 for _ in A]
    
    # Store length of A for pretty code
    n = len(A)
    
    # For each entry...
    for i in range(n):
        # Select random int from 1 to n, the same as creating some P but more memory efficient
        p_i = random.randint(1, n)
        
        # Update A_prime accoring to notes
        A_prime[p_i - 1] += A[i]
    return A_prime


# KK algorithm
def karmarkarKarp(A):
    # Negate entries to make the min-heap a max-heap
    A_prime = [-a for a in A]
    
    # Heapify list and initialize return val
    heapq.heapify(A_prime)

    # Exit when only one element is left
    while len(A_prime) > 1:
        
        # Take largest 2 elements (can do blindly because of while condition)
        top_1 = heapq.heappop(A_prime)
        top_2 = heapq.heappop(A_prime)
        
        # Calculate residual
        res = top_1 - top_2
        
        # Only add residual back if non-zero, else return 0
        if not res:
            return res
        heapq.heappush(A_prime, res)


    return abs(A_prime[0])
    


# Implementation of repeated random alg
def repeatedRandom(A):
    return None


# Implementatoin of hill climb alg
def hillClimbing(A):
    return None


# Implementation of simulated Annealing alg
def simulatedAnnealing(A):
    return None


# Code that handles inputs and calls algorithms
def main():
    if len(sys.argv) != 4:
        raise ValueError(f"Improper input lenght. file ")
    
    A = []
    
    # Read file input/extract number list
    with open(sys.argv[3], "r") as f:

        # Read each number line by line
        line = f.readline()
    
        
        # Add numbers to list until we run out (100 numbers)
        while line:
            A.append(int(line))
            line = f.readline()
    
    # Save the alg tag
    alg = sys.argv[2]
    
    # If prepartion alg, then pre-partition (turn A into A') and adjust alg tag
    if len(alg) > 2:
        alg = alg[-1]
        A = prepart(A)
    
    res = None
    
    match sys.argv[2]:
        case "0":
            # Karmarkar-Karp
            res = karmarkarKarp(A)
        case "1":
            # Repeated Random
            res = repeatedRandom(A)
        case "2":
            # Hill Climbing
            res = hillClimbing(A)
        case "3":
            # Simulated Annealing
            res = simulatedAnnealing(A)
            
    # Print out the result for bbg auto grader
    print(res)
    return None


if __name__ == "__main__":
    main()