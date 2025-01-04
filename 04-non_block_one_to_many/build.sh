#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate into the build directory
cd build

# Remove the CMake cache if it exists
if [ -f "CMakeCache.txt" ]; then
  rm CMakeCache.txt
fi

BUSY_WAIT=0

print_usage() {
  echo "Usage: build.sh [-b]"
  echo "  -b: Use busy wait"
}

while getopts "b" flag; do
  case "${flag}" in
    b) BUSY_WAIT=1;;
    *) print_usage
        exit 1;;
  esac
done

# Run CMake to configure the project
cmake -DBUSY_WAIT=${BUSY_WAIT} ..

# Build the project
make