#ifndef SIGNATURE_ASSIGNMENT2_H
#define SIGNATURE_ASSIGNMENT2_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

// Signature Assignment 2 classes for reading binary data and basic analysis

// Function to create a data file with random data
void createBinaryFile(const char* filename = "binary.dat") {
    const int SIZE = 1000;
    int* values = new int[SIZE];
    
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Fill array with random values
    for (int i = 0; i < SIZE; i++) {
        values[i] = std::rand() % 1000;  // Random number between 0-999
    }
    
    // Write to binary file
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Write the length first
        int size_value = SIZE;  // Create a non-const copy
        file.write(reinterpret_cast<char*>(&size_value), sizeof(int));
        
        // Write the array values
        file.write(reinterpret_cast<char*>(values), SIZE * sizeof(int));
        
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
    
    delete[] values;
}

// BinaryReader class for reading binary data
class BinaryReader {
private:
    int* values;
    int size;
    
    // Read values from binary file
    void readValues(const char* filename) {
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            // Read the length first
            file.read(reinterpret_cast<char*>(&size), sizeof(int));
            
            // Create array based on read length
            if (values != nullptr) {
                delete[] values;
            }
            values = new int[size];
            
            // Read the array values
            file.read(reinterpret_cast<char*>(values), size * sizeof(int));
            
            file.close();
        } else {
            std::cerr << "Error: Could not open file for reading." << std::endl;
        }
    }
    
public:
    // Constructor
    BinaryReader(const char* filename) : values(nullptr), size(0) {
        readValues(filename);
    }
    
    // Destructor
    ~BinaryReader() {
        delete[] values;
    }
    
    // Return a copy of the values
    int* getValues() {
        int* copy = new int[size];
        for (int i = 0; i < size; i++) {
            copy[i] = values[i];
        }
        return copy;
    }
    
    // Return the size
    int getSize() {
        return size;
    }
};

// Basic Analyzer class (non-virtual version from Module 2)
class BasicAnalyzer {
private:
    int* values;
    int size;
    
    // Clone values
    int* cloneValues(int* original, int size) {
        int* copy = new int[size];
        for (int i = 0; i < size; i++) {
            copy[i] = original[i];
        }
        return copy;
    }
    
public:
    // Constructor
    BasicAnalyzer(int* values, int size) {
        this->values = cloneValues(values, size);
        this->size = size;
    }
    
    // Destructor
    ~BasicAnalyzer() {
        delete[] values;
    }
    
    // Analyze data
    std::string analyze() {
        // Calculate min
        int min = values[0];
        for (int i = 1; i < size; i++) {
            if (values[i] < min) {
                min = values[i];
            }
        }
        
        // Calculate max
        int max = values[0];
        for (int i = 1; i < size; i++) {
            if (values[i] > max) {
                max = values[i];
            }
        }
        
        // Calculate mean
        double mean = 0.0;
        for (int i = 0; i < size; i++) {
            mean += values[i];
        }
        mean /= size;
        
        // Format result string
        std::string result = "Min: " + std::to_string(min) + "\n";
        result += "Max: " + std::to_string(max) + "\n";
        result += "Mean: " + std::to_string(mean);
        
        return result;
    }
};

#endif // SIGNATURE_ASSIGNMENT2_H
