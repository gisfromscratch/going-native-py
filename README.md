# going-native-py
Bringing the power, stability and functional capabilities of C++ to Python.
This is just a get your hands dirty approach and should be useful for any developer who is interested in C++ and Python.

# Features
The following algorithms are offered to Python:
- std::count<int, float, string>

## Requirements
For building python modules from C++ the awesome [pybind11](https://github.com/pybind/pybind11) library is used.
The build system relies on [CMake](https://cmake.org/). During configure each C++ module copies the compiled libraries into the test folder.
The test folder contains the unit tests which are only based on Python.