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

add_library(helpers STATIC src/helpers.cpp)

add_executable(main main.cpp src/round_robin.cpp)
target_link_libraries(main ${MPI_LIBRARIES})

add_executable(main_sr main.cpp src/round_robin_sr.cpp)
target_link_libraries(main_sr ${MPI_LIBRARIES})