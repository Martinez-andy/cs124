import sys


def main():
    if len(sys.argv) != 4:
        raise ValueError(f"Improper input lenght. file ")
    
    number = []
    
    # Read file input
    with open(sys.argv[3], "r") as f:

        # Read each number line by line
        line = f.readline()
    
        
        # Add numbers to list until we run out (100 numbers)
        while line:
            number.append(int(line))
            line = f.readline()
    
    print(number)
    
    
    match sys.argv[2]:
        case "0":
            # Karmarkar-Karp
            karmarkarKarp(number)
        case "1":
            # Repeated Random
            repeatedRandom(number)
        case "2":
            # Hill Climbing
            hillClimbing(number)
        case "3":
            # Simulated Annealing
            simulatedAnnealing(number)
        case "11":
            # Prepartitioned Repeated Random
            prepartitionedRepeatedRandom(number)
        case "12":
            # Prepartitioned Hill Climbing
            prepartitionedHillClimbing(number)
        case "13":
            # Prepartitioned Simulated Annealing
            prepartitionedSimulatedAnnealing(number)

    return None



def karmarkarKarp(number):
    return None


def repeatedRandom(number):
    return None


def hillClimbing(number):
    return None


def simulatedAnnealing(number):
    return None


def prepartitionedRepeatedRandom(number):
    return None


def prepartitionedHillClimbing(number):
    return None


def prepartitionedSimulatedAnnealing(number):
    return None
    
main()