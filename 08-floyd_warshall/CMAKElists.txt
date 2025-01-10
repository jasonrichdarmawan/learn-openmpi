cmake_minimum_required(VERSION 3.10)

project(floyd_warshall)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

include_directories(include)

add_executable(main main.c
                    src/GRAPH_max_edges.c 
                    src/GRAPH_random_graph.c 
                    src/flatten_2D_double.c 
                    src/GRAPH_shortest_paths_floyd_warshall.c
                    src/MPI_GRAPH_shortest_paths_floyd_warshall.c)
target_link_libraries(main ${MPI_LIBRARIES})