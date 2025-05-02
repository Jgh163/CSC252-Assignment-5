#ifndef SIGNATURE_ASSIGNMENT4_H
#define SIGNATURE_ASSIGNMENT4_H

#include <string>
#include <cstdlib>
#include <ctime>
#include "SignatureAssignment3.h"

// Signature Assignment 4 classes and functions for advanced data analysis

// Selection sort algorithm
void selection_sort(int* values, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (values[j] < values[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = values[i];
            values[i] = values[min_idx];
            values[min_idx] = temp;
        }
    }
}

// Binary search recursive implementation
bool binary_search_recursive(int* values, int key, int start, int end) {
    if (start > end) {
        return false;
    }
    
    int mid = start + (end - start) / 2;
    
    if (values[mid] == key) {
        return true;
    }
    else if (values[mid] > key) {
        return binary_search_recursive(values, key, start, mid - 1);
    }
    else {
        return binary_search_recursive(values, key, mid + 1, end);
    }
}

// Binary search helper function
bool binary_search(int* values, int key, int size) {
    return binary_search_recursive(values, key, 0, size - 1);
}

// Simple random number generator
class SimpleRandom {
private:
    unsigned int seed;
public:
    SimpleRandom(unsigned int initial_seed = 1) : seed(initial_seed) {}
    
    // Set a new seed
    void setSeed(unsigned int new_seed) {
        seed = new_seed;
    }
    
    // Generate a random integer in range [0, max-1]
    int next(int max) {
        // Parameters for a simple LCG
        const unsigned int a = 1664525;
        const unsigned int c = 1013904223;
        
        // Update seed using LCG formula
        seed = a * seed + c;
        
        // Return value in desired range
        return static_cast<int>(seed % max);
    }
};

// Generate a seed based on the current time
unsigned int generateTimeSeed() {
    time_t now = time(0);
    return static_cast<unsigned int>(now);
}

// SearchAnalyzer class that uses binary search
class SearchAnalyzer : public Analyzer {
public:
    SearchAnalyzer(int* values, int size) : Analyzer(values, size) {
        // Sort the array in constructor
        selection_sort(this->values, this->size);
    }
    
    std::string analyze() override {
        int found_count = 0;
        SimpleRandom random(generateTimeSeed() + 123);  // Different seed than data generation
        
        // Generate 100 random numbers and search for them
        for (int i = 0; i < 100; i++) {
            int random_value = random.next(values[size-1] + 1);  // Random value in range of data
            if (binary_search(values, random_value, size)) {
                found_count++;
            }
        }
        
        // Return result as a string
        return "There were " + std::to_string(found_count) + 
               " out of 100 random values found";
    }
};

// Enhanced StatisticsAnalyzer class with median and mode
class EnhancedStatisticsAnalyzer : public Analyzer {
public:
    EnhancedStatisticsAnalyzer(int* values, int size) : Analyzer(values, size) {}
    
    std::string analyze() override {
        // Sort the array first
        selection_sort(values, size);
        
        // Min and max values are now at the beginning and end of the sorted array
        int min_value = values[0];
        int max_value = values[size - 1];
        
        // Calculate mean (average)
        double mean = 0.0;
        for (int i = 0; i < size; i++) {
            mean += values[i];
        }
        mean /= size;
        
        // Calculate median
        double median = 0.0;
        if (size % 2 == 0) {
            // Even number of elements - average of middle two values
            median = (values[size/2 - 1] + values[size/2]) / 2.0;
        } else {
            // Odd number of elements - middle value
            median = values[size/2];
        }
        
        // Calculate mode (most frequent value)
        int mode_value = 0;
        int mode_count = 0;
        
        int current_value = values[0];
        int current_count = 1;
        
        // Since the array is sorted, we can count consecutive occurrences
        for (int i = 1; i < size; i++) {
            if (values[i] == current_value) {
                current_count++;
            } else {
                if (current_count > mode_count) {
                    mode_count = current_count;
                    mode_value = current_value;
                }
                current_value = values[i];
                current_count = 1;
            }
        }
        
        // Check the last sequence
        if (current_count > mode_count) {
            mode_count = current_count;
            mode_value = current_value;
        }
        
        // Format results
        std::string result = "The minimum value is " + std::to_string(min_value) + "\n";
        result += "The maximum value is " + std::to_string(max_value) + "\n";
        result += "The mean value is " + std::to_string(mean) + "\n";
        result += "The median value is " + std::to_string(median) + "\n";
        result += "The mode value is " + std::to_string(mode_value) + 
                  " which occurred " + std::to_string(mode_count) + " times";
        
        return result;
    }
};

#endif // SIGNATURE_ASSIGNMENT4_H
