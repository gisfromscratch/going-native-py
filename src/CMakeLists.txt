cmake_minimum_required (VERSION 3.0.0)

project (algorithm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Skip vcpkg for now and use system pybind11
# include($ENV{vcpkg_root}/scripts/buildsystems/vcpkg.cmake)

# Find python and pybind11
find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

add_subdirectory (algorithm)
# Skip io module for now
# add_subdirectory (io)