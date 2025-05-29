# going-native-py
Bringing the power, stability and functional capabilities of C++ to Python.
This is just a get your hands dirty approach and should be useful for any developer who is interested in C++ and Python.

# Features
The following STL algorithms are exposed to Python through pybind11:

## Core Algorithms
- **count**: Count occurrences of a value (int, float, string, time_point)
- **count_lt**: Count elements less than a threshold (int, float, string, time_point)
- **sort**: Returns a sorted copy of the list (int, float, string, time_point)
- **reverse**: Returns a reversed copy of the list (int, float, string, time_point)
- **accumulate**: Sum elements with an initial value (int, float)
- **min_element/max_element**: Find minimum/maximum values (int, float, string, time_point)

## Transform Operations
- **transform_square**: Square each numeric element (int, float)
- **transform_abs**: Absolute value of each numeric element (int, float)
- **transform_sqrt**: Square root of each float element (float only)
- **transform_toupper/tolower**: String case conversion (string only)

## Search and Selection
- **binary_search**: Fast O(log n) search in sorted sequences (int, float, string, time_point)
- **nth_element**: Find the nth smallest element (int, float, string, time_point)
- **unique**: Remove adjacent duplicate elements (int, float, string, time_point)

## Set Operations (for sorted sequences)
- **set_union**: Union of two sorted lists (int, float, string)
- **set_intersection**: Intersection of two sorted lists (int, float, string)
- **set_difference**: Elements in first list but not second (int, float, string)
- **includes**: Check if first sorted list includes all elements of second (int, float, string)

## Sequence Manipulation
- **partition_less_than**: Partition elements around a threshold (int, float, string)
- **rotate_left**: Rotate sequence left by specified positions (int, float, string)

## Array Operations
- **count_arr**: Count occurrences in numpy arrays (int only)

## Notes
The functions expect array/list values not being ```nan```. When using pandas dataframes for instance do a ```DataFrame[<column_name>].dropna()``` to get rid of optional values. Optional values are supported with C++17, I did not implemented any backport for C++11. The offered C++ modules are compiled with language features of C++11.

## Requirements
For building python modules from C++ the awesome [pybind11](https://github.com/pybind/pybind11) library is used.
The build system relies on [CMake](https://cmake.org/). During configure each C++ module copies the compiled libraries into the test folder.
The test folder contains the unit tests which are only based on Python.

## Contributing
Contributions are welcome from anyone and everyone. Please see our [guidelines](CONTRIBUTING.md).