#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate into the build directory
cd build

# Run CMake to configure the project
cmake ..

# Build the project
make