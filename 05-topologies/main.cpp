#include <mpi.h>
#include "cart-topo.hpp"
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    MPI_Comm comm_cart;
    int rank;

    const int ndims = 2;
    const int DIMS_0 = 4;
    const int DIMS_1 = 2;
    const int dims[] = { DIMS_0, DIMS_1 };
    const int periodic[] = { 1, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, // Input communicator
                    ndims,          // Number of Cartesian dimensions
                    dims,           // Process per dimension
                    periodic,       // Periodic (per dimension)
                                    // does each dimension "wrap around"?
                    0,              // Reorder rankings?
                    &comm_cart);    // Cartesian communicator
    MPI_Comm_rank(comm_cart, &rank); // Get the rank of the process in the communicator

    mapper(rank, dims, comm_cart);
    neighbors(rank, dims, comm_cart);

    MPI_Finalize();
    return 0;
}
