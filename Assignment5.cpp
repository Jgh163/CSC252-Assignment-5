#include <iostream>
#include <string>
#include <fstream>

// Include SignatureAssignment headers
#include "SignatureAssignment1.h" // Binary file operations
#include "SignatureAssignment2.h" // BinaryReader and basic Analyzer
#include "SignatureAssignment3.h" // Abstract Analyzer and subclasses
#include "SignatureAssignment4.h" // Sorting, searching and enhanced statistics

using namespace std;

int main() {
    // Create a data file with random data if it doesn't exist
    string filename = "data.dat";
    createBinaryFile(filename.c_str());
    
    // Read the data using BinaryReader class from SignatureAssignment2
    BinaryReader reader(filename.c_str());
    int* values = reader.getValues();
    int size = reader.getSize();
    
    // Use different analyzers and display results
    cout << "Statistical Analysis:" << endl;
    EnhancedStatisticsAnalyzer statsAnalyzer(values, size);
    cout << statsAnalyzer.analyze() << endl << endl;
    
    cout << "Duplicates Analysis:" << endl;
    DuplicatesAnalyser dupAnalyser(values, size);
    cout << dupAnalyser.analyze() << endl << endl;
    
    cout << "Missing Values Analysis:" << endl;
    MissingAnalyzer missAnalyser(values, size);
    cout << missAnalyser.analyze() << endl << endl;
    
    cout << "Search Analysis:" << endl;
    SearchAnalyzer searchAnalyzer(values, size);
    cout << searchAnalyzer.analyze() << endl;
    
    // Clean up
    delete[] values;
    
    return 0;
}
