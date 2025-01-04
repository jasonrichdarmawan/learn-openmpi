cmake_minimum_required(VERSION 3.10)

project(non_block_one_to_many)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

include_directories(include)

add_library(helpers STATIC src/helpers.cpp)

add_executable(main main.cpp src/non_block_one_to_many.cpp)
target_link_libraries(main helpers ${MPI_LIBRARIES})

option(BUSY_WAIT "BUSY_WAIT" 0)

target_compile_definitions(main PRIVATE BUSY_WAIT=${BUSY_WAIT})