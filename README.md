# Assignment 5

## Overview
This C++ program is for assignment 5 in CSC252 Programming in C++

## Features
- Reading and writing data to/from files
- Selection sort implementation
- Binary search with recursive implementation
- Statistical analysis (min, max, mean, median, mode)
- Duplicate value detection
- Missing value identification
- Random value search analysis

## Components

### Core Functions
- `selection_sort`: Implements the selection sort algorithm
- `binary_search`: A helper function that calls the recursive binary search
- `binary_search_recursive`: Implements a recursive binary search algorithm

### Utility Classes
- `SimpleRandom`: A custom random number generator
- `DataReader`: Handles reading data from files

### Analysis Classes
- `Analyzer`: Base class for all analyzers
- `StatisticsAnalyser`: Calculates statistical measures (min, max, mean, median, mode)
- `DuplicatesAnalyser`: Identifies duplicate values
- `MissingAnalyser`: Identifies missing values in a sequence
- `SearchAnalyzer`: Tests for presence of random values using binary search

## Example Output
```
Statistical Analysis:
The minimum value is 0
The maximum value is 999
The mean value is 499.495000
The median value is 497
The mode value is 81 which occurred 5 times

Duplicates Analysis:
There were 269 duplicated values

Missing Values Analysis:
There were 361 missing values

Search Analysis:
There were 67 out of 100 random values found
```