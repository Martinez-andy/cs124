import numpy as np
import random
import heapq
import math
import sys



# Global var(s)
max_iter = 60000

# The temperature function used in simulated annealing
def T(iter):
    return pow(10, 10) * pow(0.8, math.floor(iter / 300))


# Takes in sequence A and returns A' (used for pre-partitioned algs)
def prepart(A):
    # Initialize A and P
    A_prime = [0 for _ in A]
    P = [random.randint(0, len(A) - 1) for _ in A]
    
    
    # For each entry...
    for i, ele in enumerate(A):
        
        # Update A_prime accoring to notes
        A_prime[P[i]] += ele
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
    
    residual = abs(s1 - s2)
    
    # Iterate over max_iter
    for _ in range(1, max_iter):
        # For each set residual equal to minimum of both
        s1_prime, s2_prime, _ = getRandSol(A)
        residual = min(residual, abs(s1_prime - s2_prime))
    return residual


# Implementatoin of hill climb alg
def hillClimbing(A):
    # Get a random starting point
    s1, s2, asgmt = getRandSol(A)
    
    for _ in range(1, max_iter):
        # Initialize/update temps
        tmp1, tmp2 = s1, s2
        
        # Choose random index
        switch = random.randint(0, len(A) - 1)
        
        # Calculate residual if ele at switch index changes sets 
        if asgmt[switch]: # If in set 1 then...
            tmp1 -= A[switch]
            tmp2 += A[switch]
        else: # Else, it's in set 2 so...
            tmp2 -= A[switch]
            tmp1 += A[switch]
            
        # If temp res < curr res, then update sets and s1/s2 to smaller one
        if abs(tmp1 - tmp2) < abs(s1 - s2):
            asgmt[switch] = not asgmt[switch]
            s1, s2 = tmp1, tmp2

    return abs(s1 - s2)













# Implementation of simulated Annealing alg
def simulatedAnnealing(A):
    # Get a random starting point
    s1, s2, asgmt = getRandSol(A)
    
    # Initialize s''
    s1p, s2p, asgmtp = s1, s2, asgmt
    
    for iter in range(1, max_iter):
        # Initialize/update temps
        tmp1, tmp2 = s1, s2
        
        # Choose random index to switch (random neighbor)
        switch = random.randint(0, len(A) - 1)
        
        # Calculate residual of neighbor
        if asgmt[switch]:
            tmp1 -= A[switch]
            tmp2 += A[switch]
        else:
            tmp2 -= A[switch]
            tmp1 += A[switch]
            
        # If temp res < curr res, then update sets and s1/s2 to smaller one
        if abs(tmp1 - tmp2) < abs(s1 - s2): 
            asgmt[switch] = not asgmt[switch]
            s1, s2 = tmp1, tmp2
        elif random.random() <= np.exp(- ((abs(tmp1 - tmp2)) - (abs(s1 - s2))) / (T(iter))):
            asgmt[switch] = not asgmt[switch]
            s1, s2 = tmp1, tmp2
        
        # s'' = s condition
        if abs(s1 - s2) < abs(s1p - s2p):
            asgmtp = asgmt
            s1p, s2p = s1, s2

    return abs(s1p - s2p)


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
    if len(alg) > 1:
        alg = alg[-1]
        
        A = prepart(A)
    
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
            
    # Print out the result for bbg auto grader
    print(res)
    return None


if __name__ == "__main__":
    main()