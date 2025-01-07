#ifndef MPI_MAT_VECT_READ_FILE_H
#define MPI_MAT_VECT_READ_FILE_H

#include <mpi.h>

void MPI_Mat_vect_read_file(const char *filename,
                            double **local_mat, 
                            double **vect, 
                            int *local_rows, 
                            int *rows,
                            int *cols,
                            MPI_Comm comm);

#endif // MPI_MAT_VECT_READ_FILE_H