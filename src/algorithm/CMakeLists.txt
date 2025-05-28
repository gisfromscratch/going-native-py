pybind11_add_module (algorithm py_algorithm.cpp py_algorithm.hpp
    py_data.cpp py_data.hpp
)

# rename the target output
set_target_properties(algorithm PROPERTIES OUTPUT_NAME algorithm.so)



file (GLOB ALGORITHM_PYMOD
    "../../build/algorithm/*.so"
    "../../build/algorithm/*.dll"
)

#[[
message (NOTICE "Copying " ${ALGORITHM_PYMOD} " into test folder...")
file(COPY ${ALGORITHM_PYMOD} DESTINATION "../../test")
]]

add_custom_command (
    TARGET algorithm POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:algorithm> "../../test/"
    COMMENT "Copying algorithm module to test directory"
)