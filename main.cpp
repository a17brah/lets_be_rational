#include <iostream>
#include <chrono>
#include "lets_be_rational.h"

int main() {
    const int iterations = 10000; // Number of iterations for benchmarking

    // Start the timer
    double price = 18.05;
    double F = 10000;
    double K = 23000;
    double T = 5.0;
    double q = 1.0;
    auto start = std::chrono::high_resolution_clock::now();

    // Execute the benchmarked code
    double implied_volatility;
    for (int i = 0; i < iterations; ++i) {
        implied_volatility = implied_volatility_from_a_transformed_rational_guess(price, F, K, T, q);
    }

    // Calculate the elapsed time in nanoseconds
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Print the benchmark results
    std::cout << "Benchmark completed in " << duration.count()/iterations << " nanoseconds." << std::endl;
    std::cout << implied_volatility << std::endl;
    return 0;
}