#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function declarations
void selection_sort(int* values, int size);
bool binary_search_recursive(int* values, int key, int start, int end);
bool binary_search(int* values, int key, int size);
void createDataFile(string filename);
void writeData(string filename, int* values, int length);

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

// Selection sort implementation
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

// Simple random number generator using linear congruential generator
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
    // Use a combination of values from the time to create a seed
    time_t now = time(0);
    return static_cast<unsigned int>(now);
}

// Helper function to create data file with random data
void createDataFile(string filename) {
    const int size = 1000;
    int* values = new int[size];
    
    // Generate random values using our simple random generator with time-based seed
    SimpleRandom random(generateTimeSeed());
    
    // Add gaps in the data to ensure missing values
    bool skip = false;
    int val = 0;
    for (int i = 0; i < size; i++) {
        // Occasionally skip values to create gaps
        if (i > 0 && random.next(100) < 25) {  // 25% chance to skip
            val += random.next(5) + 1;  // Skip 1-5 values
        }
        values[i] = val;
        val++;
        
        // Occasionally add duplicates
        if (random.next(100) < 20) {  // 20% chance for duplicate
            if (i + 1 < size) {
                values[i + 1] = values[i];
                i++;
            }
        }
    }
    
    // Shuffle the array to ensure it's not already sorted
    for (int i = 0; i < size; i++) {
        int j = random.next(size);
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
    }
    
    writeData(filename, values, size);
    delete[] values;
}

// Write array to data file
void writeData(string filename, int* values, int length) {
    ofstream file(filename);
    if (file.is_open()) {
        file << length << endl;
        for (int i = 0; i < length; i++) {
            file << values[i] << endl;
        }
        file.close();
    } else {
        cerr << "Error: Could not open file for writing." << endl;
    }
}

// DataReader class for reading data
class DataReader {
private:
    int* values;
    int size;
    
public:
    DataReader(string filename) : values(nullptr), size(0) {
        readValues(filename);
    }
    
    ~DataReader() {
        delete[] values;
    }
    
    int* getValues() {
        // Create a copy of the values to return
        int* copy = new int[size];
        for (int i = 0; i < size; i++) {
            copy[i] = values[i];
        }
        return copy;
    }
    
    int getSize() {
        return size;
    }
    
    void readValues(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            // First read the size
            file >> size;
            
            // Allocate memory for values
            if (values != nullptr) {
                delete[] values;
            }
            values = new int[size];
            
            // Read the values
            for (int i = 0; i < size; i++) {
                file >> values[i];
            }
            file.close();
        } else {
            cerr << "Error: Could not open file for reading." << endl;
        }
    }
};

// Base Analyzer class
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
    
    virtual string analyze() = 0;
};

// DuplicatesAnalyser class
class DuplicatesAnalyser : public Analyzer {
public:
    DuplicatesAnalyser(int* values, int size) : Analyzer(values, size) {}
    
    string analyze() override {
        // Sort the array first
        selection_sort(values, size);
        
        int duplicateCount = 0;
        for (int i = 1; i < size; i++) {
            if (values[i] == values[i-1]) {
                duplicateCount++;
                // Skip any additional duplicates of the same value
                while (i+1 < size && values[i+1] == values[i]) {
                    i++;
                }
            }
        }
        
        return "There were " + to_string(duplicateCount) + " duplicated values";
    }
};

// MissingAnalyser class
class MissingAnalyser : public Analyzer {
public:
    MissingAnalyser(int* values, int size) : Analyzer(values, size) {}
    
    string analyze() override {
        // Sort the array first
        selection_sort(values, size);
        
        int missingCount = 0;
        for (int i = 1; i < size; i++) {
            missingCount += (values[i] - values[i-1] - 1);
        }
        
        return "There were " + to_string(missingCount) + " missing values";
    }
};

// SearchAnalyzer class
class SearchAnalyzer : public Analyzer {
public:
    SearchAnalyzer(int* values, int size) : Analyzer(values, size) {
        // Sort the array in constructor
        selection_sort(this->values, this->size);
    }
    
    string analyze() override {
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
        return "There were " + to_string(found_count) + 
               " out of 100 random values found";
    }
};

// StatisticsAnalyser class
class StatisticsAnalyser : public Analyzer {
public:
    StatisticsAnalyser(int* values, int size) : Analyzer(values, size) {}
    
    string analyze() override {
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
        
        // Format results with fixed precision for mean
        string mean_str = to_string(mean);
        // Truncate to 6 decimal places
        size_t decimal_pos = mean_str.find('.');
        if (decimal_pos != string::npos) {
            size_t max_length = decimal_pos + 7; // Include the decimal point and 6 digits
            if (mean_str.length() > max_length) {
                mean_str = mean_str.substr(0, max_length);
            }
        }
        
        string result = "The minimum value is " + to_string(min_value) + "\n";
        result += "The maximum value is " + to_string(max_value) + "\n";
        result += "The mean value is " + mean_str + "\n";
        result += "The median value is " + to_string((int)median) + "\n";
        result += "The mode value is " + to_string(mode_value) + 
                  " which occurred " + to_string(mode_count) + " times";
        
        return result;
    }
};

int main() {
    // Create a data file with random data if it doesn't exist
    string filename = "data.dat";
    createDataFile(filename);
    
    // Read the data
    DataReader reader(filename);
    int* values = reader.getValues();
    int size = reader.getSize();
    
    // Use different analyzers and display results
    cout << "Statistical Analysis:" << endl;
    StatisticsAnalyser statsAnalyzer(values, size);
    cout << statsAnalyzer.analyze() << endl << endl;
    
    cout << "Duplicates Analysis:" << endl;
    DuplicatesAnalyser dupAnalyser(values, size);
    cout << dupAnalyser.analyze() << endl << endl;
    
    cout << "Missing Values Analysis:" << endl;
    MissingAnalyser missAnalyser(values, size);
    cout << missAnalyser.analyze() << endl << endl;
    
    cout << "Search Analysis:" << endl;
    SearchAnalyzer searchAnalyzer(values, size);
    cout << searchAnalyzer.analyze() << endl;
    
    // Clean up
    delete[] values;
    
    return 0;
}