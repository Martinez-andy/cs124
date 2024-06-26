import numpy as np
import random
import heapq
import math
import sys

# Global var(s)
max_iter = 35000

# The temperature function used in simulated annealing
def T(iter):
    return pow(10, 10) * pow(0.8, math.floor(iter / 300))
    
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
   
   
# repeatRandom/hill Climb Helper function
def getRandSol(A):
    # Keep track of sums and of which set each is in
    fst_sum = 0
    snd_sum = 0
    asgmt = []

    # Iterate over each element and add them to either set randomly
    for ele in A:
        # Assign elements into a set
        in_set_one = bool(random.randint(0, 1))
        
        # Add ele to respective sum depending on set
        if in_set_one:
            fst_sum += ele
        else:
            snd_sum += ele

        # Indicate if in set one or not
        asgmt.append(in_set_one)
            
    return fst_sum, snd_sum, asgmt 


# Implementation of repeated random alg
def repeatedRandom(A):
    # Initialize random solution
    s1, s2, _ = getRandSol(A)
    
    # Iterate over max_iter
    for _ in range(1, max_iter):
        # For each set residual equal to minimum of both
        s1_prime, s2_prime, _ = getRandSol(A)
        
        # If solution is better, then update
        if abs(s1_prime - s2_prime) < abs(s1 - s2):
            s1, s2 = s1_prime, s2_prime

    return abs(s1 - s2)


def swap(s1, s2, i, A, asgmt):
    if asgmt[i]:
        s1 += A[i]
        s2 -= A[i]
    else:
        s2 += A[i]
        s1 -= A[i]
        
    asgmt[i] = not asgmt[i]
    
    return s1, s2, asgmt

# Implementatoin of hill climb alg
def hillClimbing(A):
    # Get a random starting point
    s1, s2, asgmt = getRandSol(A)
    
    i1 = i2 = 0
    
    for _ in range(1, max_iter):
        # Initialize/update temps
        tmp1, tmp2 = s1, s2
        
        # Do while loop until indices aren't equal
        while True:
            i1, i2 = random.randint(0, len(A) - 1), random.randint(0, len(A) - 1)
            if i1 != i2:
                break
        
        # Swap i1's sign
        tmp1, tmp1, tmp_asgmt = swap(tmp1, tmp2, i1, A, asgmt)
        
        # Swap i2 w prob 50%
        if random.random() <= 0.5:
            tmp1, tmp2, tmp_asgmt = swap(tmp1, tmp2, i2, A, tmp_asgmt)
            
        # If temp res < curr res, then update sets and s1/s2 to smaller one
        if abs(tmp1 - tmp2) < abs(s1 - s2):
            asgmt = tmp_asgmt
            s1, s2 = tmp1, tmp2

    return abs(s1 - s2)


# Implementation of simulated Annealing alg
def simulatedAnnealing(A):
    # Get a random starting point
    s1, s2, asgmt = getRandSol(A)
    
    i1 = i2 = 0
    
    for iter in range(1, max_iter):
        # Initialize/update temps
        tmp1, tmp2 = s1, s2
        
        # Do while loop until indices aren't equal
        while True:
            i1, i2 = random.randint(0, len(A) - 1), random.randint(0, len(A) - 1)
            if i1 != i2:
                break
        
        # Swap i1's sign
        tmp1, tmp1, tmp_asgmt = swap(tmp1, tmp2, i1, A, asgmt)
        
        # Swap i2 w prob 50%
        if random.random() <= 0.5:
            tmp1, tmp2, tmp_asgmt = swap(tmp1, tmp2, i2, A, tmp_asgmt)
            
        # If temp res < curr res, then update sets and s1/s2 to smaller one
        if abs(tmp1 - tmp2) < abs(s1 - s2):
            asgmt = tmp_asgmt
            s1, s2 = tmp1, tmp2
        elif random.random() <= np.exp(- (abs(tmp1 - tmp2) - abs(s1 - s2)) / (T(iter))):
            asgmt = tmp_asgmt
            s1, s2 = tmp1, tmp2

    return abs(s1 - s2)




# ALGORITHMS FOR PRE-PART PORTION 


# PRE-PART HELP FUNCTIONS

# Takes in sequence A and returns A' (used for pre-partitioned algs)
def prepart(A, P=None):
    # Initialize A and P
    A_prime = [0 for _ in A]
    
    # If a P is not given, then create a random one
    if not P:
        P = [random.randint(0, len(A) - 1) for _ in A]
    
    # For each entry...
    for i, ele in enumerate(A):
        
        # Update A_prime accoring to notes
        A_prime[P[i]] += ele
        
    return A_prime, P


# Takes in a set and a P and returns a neighbor
def prepartNeighbor(P):
    # Find i and j until P_i != j
    while True:
        i, j = random.randint(0, len(P) - 1), random.randint(0, len(P) - 1)
        
        if P[i] != j:
            break
    # Set P_i = j
    P[i] = j
    
    # Return modified P
    return P




# PRE-PART ACTUAL ALGORITHMS

def prepartRandom(A):
    A_prime, _ = prepart(A)
    residue = karmarkarKarp(A_prime)

    
    for _ in range(1, max_iter):
        A_temp, _ = prepart(A)
        
        res_temp = karmarkarKarp(A_temp)
        
        residue = min(residue, res_temp)
    
    return residue
            

def prepartHill(A):
    A_prime, P = prepart(A)
    
    res = karmarkarKarp(A_prime)
    
    for _ in range(max_iter):
        # Find neighbors
        new_P = prepartNeighbor(P)
        
        # Find new A value
        new_A, new_P = prepart(A, new_P)
        
        # Calculate new_res
        new_res = karmarkarKarp(new_A)
        
        if new_res < res:
            res = new_res
            P = new_P
        
    return res


def prepartSim(A):
    A_prime, P = prepart(A)
    
    res = karmarkarKarp(A_prime)
    
    for iter in range(max_iter):
        # Find neighbors
        new_P = prepartNeighbor(P)
        
        # Find new A value
        new_A, new_P = prepart(A, new_P)
        
        # Calculate new_res
        new_res = karmarkarKarp(new_A)
        
        if new_res < res:
            res = new_res
            P = new_P
        elif random.random() <= np.exp(- (new_res - res)) / (T(iter)):
            res = new_res
            P = new_P
        
    return res


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
    
    res = None
    
    match alg:
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
        case "11":
            res = prepartRandom(A)
        case "12":
            res = prepartHill(A)
        case "13":
            res = prepartSim(A)
            
            
    # Print out the result for bbg auto grader
    print(res)
    return None


if __name__ == "__main__":
    main()