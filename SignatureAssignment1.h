#ifndef SIGNATURE_ASSIGNMENT1_H
#define SIGNATURE_ASSIGNMENT1_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Signature Assignment 1 functions for binary file operations

// Create an array of random integers
int* createArray(int* length) {
    const int SIZE = 1000;
    *length = SIZE;
    
    int* values = new int[SIZE];
    
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Fill array with random values
    for (int i = 0; i < SIZE; i++) {
        values[i] = std::rand() % 1000;  // Random number between 0-999
    }
    
    return values;
}

// Write array to binary file
void writeBinary(int* values, int length, const char* filename = "binary.dat") {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Write the length first
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        
        // Write the array values
        file.write(reinterpret_cast<char*>(values), length * sizeof(int));
        
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

// Read array from binary file
int* readBinary(int& length, const char* filename = "binary.dat") {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Read the length first
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        
        // Create array based on read length
        int* values = new int[length];
        
        // Read the array values
        file.read(reinterpret_cast<char*>(values), length * sizeof(int));
        
        file.close();
        return values;
    } else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
        length = 0;
        return nullptr;
    }
}

#endif // SIGNATURE_ASSIGNMENT1_H
