#ifndef MPI_MAT_VECT_SCATTER_ROW_H
#define MPI_MAT_VECT_SCATTER_ROW_H

#include <mpi.h>

void MPI_Mat_vect_scatter_row(const double *mat,
                              double **local_mat,
                              double **vect,
                              int *local_rows,
                              const int *rows,
                              const int *cols,
                              MPI_Comm comm);

#endif // MPI_MAT_VECT_SCATTER_ROW_H