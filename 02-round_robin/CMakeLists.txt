cmake_minimum_required(VERSION 3.10)

# Project name
project(round_robin)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find MPI package
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add the include directory
include_directories(include)

# Add the executable
add_executable(main main.cpp src/round_robin.cpp)

# Link the MPI libraries
target_link_libraries(main ${MPI_LIBRARIES})