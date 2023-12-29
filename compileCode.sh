#!/bin/sh

# Change directory to cppProject
cd cppProject || exit

# Create directory if it doesn't exist
mkdir -p build

# Change directory to the newly created 'build' directory
cd build || exit

# Run CMake to configure the build
#cmake ..
cmake -Dvar=tutorial.cpp ..

# Use 'make' to compile the project
make

# Run the executable
./MyProject
