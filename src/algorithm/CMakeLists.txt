# TODO: Change this path to your local vcpkg repository
include(~/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package (pybind11 CONFIG REQUIRED)

pybind11_add_module (algorithm py_algorithm.cpp py_algorithm.hpp)