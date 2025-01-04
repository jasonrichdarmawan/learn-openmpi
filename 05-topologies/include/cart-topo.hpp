#ifndef CART_TOPO_H
#define CART_TOPO_H

#include <mpi.h>

void mapper(int rank, const int *dims, MPI_Comm comm_cart);
void neighbors(int rank, const int *dims, MPI_Comm comm_cart);

#endif // CART_TOPO_H