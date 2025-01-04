cmake_minimum_required(VERSION 3.10)

project(non_block_one_to_many)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

include_directories(include)

add_library(helpers STATIC src/helpers.cpp)

add_executable(main main.cpp src/cart-topo.cpp)
target_link_libraries(main helpers ${MPI_LIBRARIES})

option(PRINT_MAP "PRINT_MAP" 0)
option(PRINT_NEIGHBORS "PRINT_NEIGHBORS" 0)
target_compile_definitions(main PRIVATE PRINT_MAP=${PRINT_MAP} PRINT_NEIGHBORS=${PRINT_NEIGHBORS})