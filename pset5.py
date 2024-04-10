import random

# n value that we are testing 
n = 63973

# Calculate GCD
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# Finds u and t according to the notes:  n - 1 = 2^t * u
def find_u_and_t(n):
    u = n - 1
    t = 0
    while u % 2 == 0:
        u //= 2
        t += 1
    return u, t

# Find u and t
u, t = find_u_and_t(n)

# Used for Rabin's alg
def find_real_a(a, i):
    power = pow(2, i - 1) * u
    real_a = pow(a, power, n)
    print(real_a)
    return

# Fermat's test + Rabin's test
def notesAlg(n):
    for _ in range(100):
        a = random.randint(1, n)


        # Uses Fermat's Test
        if pow(a, n - 1, n) != 1:
            if gcd(a, n) == 1:
                print(f"n is composite by Fermat's. Witness: {a}")
                return None

        # If Fermat's fails, moves onto Rabin's test from notes
        for i in range(1, t + 1):
            cPower = pow(2, i)
            res1 = pow(a, cPower * u, n)
            if res1 == 1:
                newcPower = pow(2, i - 1)
                res2 = pow(a, newcPower * u, n)
                if res2 != 1 and res2 != -1:
                    if gcd(a, n) == 1:
                        print(f"n is composite by Rabin's. Witness: {a} with power {i}")
                        print(f'REAL A: {res2}')
                        find_real_a(a, i)
                        return None
        
notesAlg(n)







"""
def is_witness(a, n):
    r1 = pow(a, n-1, n) != 1
    r2 = pow(a, (n-1) // 2, n) != 1 and pow(a, (n-1) // 2, n) != n - 1
    print(r1)
    print(r2)
    return r1 or r2

found_witness = False

for i in range(t):
    # Calculate the power of 2 times u
    exp = pow(2, i) * u
    
    # Compute a^(2^{i}u) mod n
    result = pow(a, exp, n)
    
    # Check the conditions
    if result != 1 and result != n - 1:
        found_witness = True
        break

# Check if a witness was found
if found_witness:
    print(f"A witness was found for n = {n}: a = {a}")
else:
    print("No witness was found for n =", n)
    
is_witness(a, n)

def find_u_and_t(n):
    u = n - 1
    t = 0
    while u % 2 == 0:
        u //= 2
        t += 1
    print(u, t)
    return u, t

"""

    