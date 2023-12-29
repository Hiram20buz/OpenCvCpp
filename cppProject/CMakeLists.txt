cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Check if an argument 'var' is provided
if(NOT DEFINED var)
    message(FATAL_ERROR "Please provide a source file name using '-Dvar=<source_file.cpp>'")
endif()

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Create an executable using the provided 'var' argument
add_executable(MyProject ${var})

# Link OpenCV libraries
target_link_libraries(MyProject ${OpenCV_LIBS})