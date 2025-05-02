# CSC252 Signature Assignment

This project is a compilation of all signature assignments from CSC252 Programming in C++. The code has been organized into modular components based on each signature assignment.

## Project Structure

- **SignatureAssignment1.h**: Binary file operations (Module 1)
- **SignatureAssignment2.h**: BinaryReader and basic Analyzer classes (Module 2)
- **SignatureAssignment3.h**: Abstract Analyzer class and specialized analyzers (Module 3)
- **SignatureAssignment4.h**: Sorting, searching, and enhanced analyzers (Module 4)
- **Assignment5.cpp**: Main program that utilizes all components

## Pseudocode Overview

### Signature Assignment 1

#### createArray(length):
```
function createArray(length):
    SIZE = 1000
    set length* = SIZE
    allocate array of SIZE integers
    initialize random number generator
    for i from 0 to SIZE-1:
        array[i] = random number between 0-999
    return array
```

#### writeBinary(values, length, filename):
```
function writeBinary(values, length, filename):
    open binary file with filename for writing
    if file opened successfully:
        write length to file
        write values array to file
        close file
    else:
        display error message
```

#### readBinary(length, filename):
```
function readBinary(length, filename):
    open binary file with filename for reading
    if file opened successfully:
        read length from file
        allocate new array of length integers
        read values from file into array
        close file
        return array
    else:
        display error message
        set length = 0
        return nullptr
```

### Signature Assignment 2

#### createBinaryFile(filename):
```
function createBinaryFile(filename):
    SIZE = 1000
    allocate array of SIZE integers
    initialize random number generator
    fill array with random values
    open binary file with filename for writing
    if file opened successfully:
        write SIZE to file
        write values array to file
        close file
    else:
        display error message
    deallocate array
```

#### BinaryReader class:
```
class BinaryReader:
    private members:
        values - integer array
        size - integer
        
    private method readValues(filename):
        open binary file with filename for reading
        if file opened successfully:
            read size from file
            allocate values array of size integers
            read values from file
            close file
        else:
            display error message
    
    public constructor(filename):
        initialize values to nullptr and size to 0
        call readValues(filename)
    
    public destructor:
        deallocate values array
    
    public method getValues():
        create copy of values array
        return copy
    
    public method getSize():
        return size
```

#### BasicAnalyzer class:
```
class BasicAnalyzer:
    private members:
        values - integer array
        size - integer
    
    private method cloneValues(original, size):
        create copy of original array
        return copy
    
    public constructor(values, size):
        clone values array
        set size
    
    public destructor:
        deallocate values array
    
    public method analyze():
        find minimum value in array
        find maximum value in array
        calculate mean of all values
        return formatted string with results
```

### Signature Assignment 3

#### Analyzer abstract class:
```
class Analyzer:
    protected members:
        values - integer array
        size - integer
    
    public constructor(values, size):
        clone values array
        set size
    
    public virtual destructor:
        deallocate values array
    
    public method cloneValues(original, size):
        create copy of original array
        return copy
    
    public pure virtual method analyze():
        to be implemented by subclasses
```

#### DuplicatesAnalyser class:
```
class DuplicatesAnalyser (inherits from Analyzer):
    public constructor(values, size):
        call parent constructor
    
    public method analyze() override:
        sort the values array
        count duplicate values
        return formatted string with results
```

#### MissingAnalyzer class:
```
class MissingAnalyzer (inherits from Analyzer):
    public constructor(values, size):
        call parent constructor
    
    public method analyze() override:
        sort the values array
        count missing values between consecutive elements
        return formatted string with results
```

#### StatisticsAnalyzer class:
```
class StatisticsAnalyzer (inherits from Analyzer):
    public constructor(values, size):
        call parent constructor
    
    public method analyze() override:
        calculate min, max, and mean of values
        return formatted string with results
```

### Signature Assignment 4

#### selection_sort(values, size):
```
function selection_sort(values, size):
    for i from 0 to size-2:
        find minimum element in unsorted part
        swap with element at position i
```

#### binary_search_recursive(values, key, start, end):
```
function binary_search_recursive(values, key, start, end):
    if start > end:
        return false
    
    mid = start + (end - start) / 2
    
    if values[mid] == key:
        return true
    else if values[mid] > key:
        return binary_search_recursive(values, key, start, mid-1)
    else:
        return binary_search_recursive(values, key, mid+1, end)
```

#### binary_search(values, key, size):
```
function binary_search(values, key, size):
    return binary_search_recursive(values, key, 0, size-1)
```

#### SimpleRandom class:
```
class SimpleRandom:
    private members:
        seed - unsigned integer
    
    public constructor(initial_seed=1):
        set seed to initial_seed
    
    public method setSeed(new_seed):
        set seed to new_seed
    
    public method next(max):
        update seed using linear congruential generator formula
        return seed modulo max
```

#### generateTimeSeed():
```
function generateTimeSeed():
    return current time as unsigned integer
```

#### SearchAnalyzer class:
```
class SearchAnalyzer (inherits from Analyzer):
    public constructor(values, size):
        call parent constructor
        sort values array
    
    public method analyze() override:
        initialize count of found values to 0
        create random number generator
        for 100 iterations:
            generate random value
            use binary search to check if value exists in array
            if found, increment count
        return formatted string with results
```

#### EnhancedStatisticsAnalyzer class:
```
class EnhancedStatisticsAnalyzer (inherits from Analyzer):
    public constructor(values, size):
        call parent constructor
    
    public method analyze() override:
        sort values array
        calculate min and max from sorted array
        calculate mean of all values
        calculate median based on array size (middle value or average of two middle values)
        calculate mode (most frequent value)
        return formatted string with all statistical results
```

## Main Program Flow

```
function main():
    create data file "data.dat" with random values
    read data using BinaryReader
    display statistical analysis using EnhancedStatisticsAnalyzer
    display duplicates analysis using DuplicatesAnalyser
    display missing values analysis using MissingAnalyzer
    display search analysis using SearchAnalyzer
    clean up allocated memory
    return success
