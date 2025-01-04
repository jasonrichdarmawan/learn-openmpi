#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate into the build directory
cd build

PRINT_MAP=0
PRINT_NEIGHBORS=0

print_usage() {
  echo "Usage: build.sh [-m]"
  echo "  -m: Print map"
  echo "  -n: Print neighbors"
}

while getopts "mn" flag; do
  case "${flag}" in
    m) PRINT_MAP=1;;
    n) PRINT_NEIGHBORS=1;;
    *) print_usage
        exit 1;;
  esac
done

# Run CMake to configure the project
cmake -DPRINT_MAP=${PRINT_MAP} -DPRINT_NEIGHBORS=${PRINT_NEIGHBORS} ..

# Build the project
make