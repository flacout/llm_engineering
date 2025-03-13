
#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <ctime>
#include <random>

uint32_t lcg(uint32_t seed, uint32_t a=1664525, uint32_t c=1013904223, uint32_t m=1ULL<<32) {
    return (a * seed + c) % m;
}

int max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(min_val, max_val);
    std::vector<int> random_numbers(n);
    for(int i=0; i<n; i++) random_numbers[i] = dist(gen);
    int max_sum = INT_MIN;
    for(int i=0; i<n; i++) {
        int current_sum = 0;
        for(int j=i; j<n; j++) {
            current_sum += random_numbers[j];
            if(current_sum > max_sum) max_sum = current_sum;
        }
    }
    return max_sum;
}

int total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int total_sum = 0;
    std::mt19937 gen(initial_seed);
    std::uniform_int_distribution<uint32_t> lcg_dist(1, RAND_MAX);
    for(int i=0; i<20; i++) {
        uint32_t seed = lcg_dist(gen);
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;       // Number of random numbers
    uint32_t seed = 42;  // Initial seed for the LCG
    int min_val = -10;  // Minimum value of random numbers
    int max_val = 10;   // Maximum value of random numbers

    // Timing the function
    clock_t start_time = clock();
    int result = total_max_subarray_sum(n, seed, min_val, max_val);
    clock_t end_time = clock();
    
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << double(end_time-start_time)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
    return 0;
}
