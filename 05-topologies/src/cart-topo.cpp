#include "cart-topo.hpp"
#include <mpi.h>
#include <stdio.h>
#include "helpers.hpp"

#ifndef PRINT_MAP
#define PRINT_MAP 1
#endif

#ifndef PRINT_NEIGHBORS
#define PRINT_NEIGHBORS 1
#endif

// This function is used to map the rank to the 2D grid
// 0-axis is the number of rows
// 1-axis is the number of columns
void mapper(int rank, const int *dims, MPI_Comm comm_cart)
{
#if PRINT_MAP
    if (rank != 0) {
        return;
    }

    printf("    ");
    for (int i = 0; i < dims[1]; i++) {
        printf(" %2d", i);
    }
    printf("\n");
    printf("    ------\n");
    int coords[2]; // based number of Cartesian dimensions
    for (coords[0] = 0; coords[0] < dims[0]; coords[0]++) {
        printf("%2d |", coords[0]);
        for (coords[1] = 0; coords[1] < dims[1]; coords[1]++) {
            int rank;
            MPI_Cart_rank(comm_cart, coords, &rank); // Get the rank of the process in the communicator
            printf(" %2d", rank);
        }
        printf("\n");
    }
#endif
}

void neighbors(int rank, const int *dims, MPI_Comm comm_cart)
{
#if PRINT_NEIGHBORS
    int coords[2]; // based number of Cartesian dimensions
    MPI_Cart_coords(comm_cart,
                    rank,    // Input: rank of a process in the communicator
                    2,       // number of dimensions
                    coords); // Output: Get the coordinates of the process in the Cartesian topology
    debug(rank, "coords %d %d\n", coords[0], coords[1]);

    int up_rank, down_rank, left_rank, right_rank;

    // MPI_Cart_shift: who are my neighbors? 
    // depending on two things
    // the direction (do i want to go higher index or lower index in the cartesian plane)
    // and by how much do i want to step.
    //
    // the rank_source and rank_dest are basically 
    // be the neighbors on one side and the neighbors on the other side.
    //
    // suppose we have a 2D grid of 4x2, with periodic={1, 0}
    //     0 1
    //    ----
    // 0 | 0 1
    // 1 | 2 3
    // 2 | 4 5
    // 3 | 6 7
    //
    // MPI_Cart_shift(..., 0, 1, ...);
    // suppose the rank is 0, so
    //   6
    //   0
    //   2
    // 0 and 6 are neighbors because MPI_Cart_create(..., periodic, ...)—periodic is 1 for the 1st dimension
    MPI_Cart_shift(comm_cart,   // communicator
                   0,           // direction (dimensions of topology)
                   1,           // step size
                   &up_rank,    // source rank
                   &down_rank); // destination rank
    // MPI_Cart_shift(..., 1, 1, ...);
    // the rank is 0, so
    // -2 0 1
    // -2 because MPI_Cart_create(..., periodic, ...)—periodic is 0 for the 2nd dimension
    // which means there is no wrap around
    MPI_Cart_shift(comm_cart, 1, 1, &left_rank, &right_rank);

    debug(rank, "    %2d\n", up_rank);
    debug(rank, " %2d %2d %2d \n", left_rank, rank, right_rank);
    debug(rank, "    %2d\n", down_rank);
#endif
}