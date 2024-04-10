#include <iostream>
#include <random>
#include <cmath>

// Function to compute modular exponentiation (a^b mod n)
long long power(long long a, long long b, long long n) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b /= 2;
    }
    return result;
}

int main() {
    // Initialize values
    int u = 775198773;
    int t = 4;
    long long n = 12403180369;
    int power_of_two = std::pow(2, t);

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for choosing a random base a
    int lower_bound = 1;
    int upper_bound = n;

    // Generate a random integer within the range
    std::uniform_int_distribution<> dis(lower_bound, upper_bound);
    int a = dis(gen);

    // Check for the property
    bool found = false;
    for (int i = 1; i <= t; ++i) {
        long long exp = power(power_of_two, i - 1, n);
        long long result = power(a, exp * u, n);
        if (result != 1 && result != n - 1) {
            found = true;
            std::cout << "Witness found: " << a << std::endl;
            break;
        }
    }

    // If no witness is found, it's highly likely that n is prime
    if (!found) {
        std::cout << "No witness found. " << n << " is likely prime." << std::endl;
    }

    return 0;
}
