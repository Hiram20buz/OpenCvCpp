#!/bin/sh

# Change directory to cppProject
cd cppProject || exit

# Create directory if it doesn't exist
mkdir -p build

# Change directory to the newly created 'build' directory
cd build || exit

# Check if the 'var' argument is provided
if [ -z "$1" ]; then
    echo "Please provide a source file name as an argument."
    exit 1
fi

# Run CMake with the provided 'var' argument
cmake -Dvar="$1" ..

# Use 'make' to compile the project
make

# Run the executable
./MyProject
