# going-native-py
Bringing the power, stability and functional capabilities of C++ to Python.
This is just a get your hands dirty approach and should be useful for any developer who is interested in C++ and Python.

# Features
The following algorithms are offered to Python:
- std::count<int, float, string, time_point>

## Notes
The functions expect array/list values not being ```nan```. When using pandas dataframes for instance do a ```DataFrame[<column_name>].dropna()``` to get rid of optional values. Optional values are supported with C++17, I did not implemented any backport for C++11. The offered C++ modules are compiled with language features of C++11.

## Requirements
For building python modules from C++ the awesome [pybind11](https://github.com/pybind/pybind11) library is used.
The build system relies on [CMake](https://cmake.org/). During configure each C++ module copies the compiled libraries into the test folder.
The test folder contains the unit tests which are only based on Python.

## Contributing
Contributions are welcome from anyone and everyone. Please see our [guidelines](CONTRIBUTING.md).