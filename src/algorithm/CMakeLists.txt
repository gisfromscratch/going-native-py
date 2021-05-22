# TODO: Change this path to your local vcpkg repository
include(~/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package (pybind11 CONFIG REQUIRED)

pybind11_add_module (algorithm py_algorithm.cpp py_algorithm.hpp
    py_data.cpp py_data.hpp
)

file (GLOB ALGORITHM_PYMOD
    "../../build/algorithm/*.so"
    "../../build/algorithm/*.dll"
)

message (NOTICE "Copying " ${ALGORITHM_PYMOD} " into test folder...")
file(COPY ${ALGORITHM_PYMOD} DESTINATION "../../test")