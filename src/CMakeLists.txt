cmake_minimum_required (VERSION 3.0.0)

project (algorithm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: Change this path to your local vcpkg repository
include($ENV{vcpkg_root}/scripts/buildsystems/vcpkg.cmake)

# TODO: Install pybind11 e.g. vcpkg install pybind11:x64-linux
find_package (pybind11 CONFIG REQUIRED)

add_subdirectory (algorithm)
add_subdirectory (io)