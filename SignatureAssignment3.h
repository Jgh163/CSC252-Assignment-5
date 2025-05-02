#ifndef SIGNATURE_ASSIGNMENT3_H
#define SIGNATURE_ASSIGNMENT3_H

#include <string>

// Signature Assignment 3 classes for data analysis

// Abstract Analyzer base class
class Analyzer {
protected:
    int* values;
    int size;
    
public:
    Analyzer(int* values, int size) {
        this->values = cloneValues(values, size);
        this->size = size;
    }
    
    virtual ~Analyzer() {
        delete[] values;
    }
    
    int* cloneValues(int* original, int size) {
        int* copy = new int[size];
        for (int i = 0; i < size; i++) {
            copy[i] = original[i];
        }
        return copy;
    }
    
    // Pure virtual analyze function to be implemented by subclasses
    virtual std::string analyze() = 0;
};

// DuplicatesAnalyser class to count duplicate values
class DuplicatesAnalyser : public Analyzer {
public:
    DuplicatesAnalyser(int* values, int size) : Analyzer(values, size) {}
    
    std::string analyze() override {
        // First sort the array
        for (int i = 0; i < size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (values[j] < values[min_idx]) {
                    min_idx = j;
                }
            }
            // Swap
            if (min_idx != i) {
                int temp = values[i];
                values[i] = values[min_idx];
                values[min_idx] = temp;
            }
        }
        
        // Count duplicates
        int duplicateCount = 0;
        for (int i = 1; i < size; i++) {
            if (values[i] == values[i-1]) {
                duplicateCount++;
                // Skip additional duplicates of the same value
                while (i+1 < size && values[i+1] == values[i]) {
                    i++;
                }
            }
        }
        
        return "There were " + std::to_string(duplicateCount) + " duplicated values";
    }
};

// MissingAnalyzer class to count missing values
class MissingAnalyzer : public Analyzer {
public:
    MissingAnalyzer(int* values, int size) : Analyzer(values, size) {}
    
    std::string analyze() override {
        // First sort the array
        for (int i = 0; i < size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (values[j] < values[min_idx]) {
                    min_idx = j;
                }
            }
            // Swap
            if (min_idx != i) {
                int temp = values[i];
                values[i] = values[min_idx];
                values[min_idx] = temp;
            }
        }
        
        // Count missing values
        int missingCount = 0;
        for (int i = 1; i < size; i++) {
            missingCount += (values[i] - values[i-1] - 1);
        }
        
        return "There were " + std::to_string(missingCount) + " missing values";
    }
};

// StatisticsAnalyzer class (Module 3 version)
class StatisticsAnalyzer : public Analyzer {
public:
    StatisticsAnalyzer(int* values, int size) : Analyzer(values, size) {}
    
    std::string analyze() override {
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
        std::string result = "Minimum: " + std::to_string(min) + "\n";
        result += "Maximum: " + std::to_string(max) + "\n";
        result += "Mean: " + std::to_string(mean);
        
        return result;
    }
};

#endif // SIGNATURE_ASSIGNMENT3_H
