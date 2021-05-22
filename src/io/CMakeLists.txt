pybind11_add_module (io py_io.cpp py_io.hpp)

# TODO: Install csv-parser e.g. vcpkg install fast-cpp-csv-parser:x64-linux
find_path (FAST_CPP_CSV_PARSER_INCLUDE_DIRS "csv.h")

target_include_directories (io PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})