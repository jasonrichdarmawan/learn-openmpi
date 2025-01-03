cmake_minimum_required(VERSION 3.10)

# Project name
project(broad_barrier)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find MPI package
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add the include directory
include_directories(include)

# Create a static library for helpers
add_library(helpers STATIC src/helpers.cpp)

add_executable(main main.cpp src/broad_barrier.cpp)
target_link_libraries(main helpers ${MPI_LIBRARIES})