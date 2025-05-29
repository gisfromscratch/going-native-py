pybind11_add_module (algorithm py_algorithm.cpp py_algorithm.hpp
    py_data.cpp py_data.hpp
)

# Copying target native module to the test directory
message (NOTICE "Copying algorithm module into test folder...")
add_custom_command (
    TARGET algorithm POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:algorithm> "../../test/"
    COMMENT "Copying algorithm module to test directory"
)
