#include "MPI_Mat_vect_read_file.h"
#include <mpi.h>
#include "Mat_vect_read_file.h"
#include "MPI_Mat_vect_scatter_row.h"
#include <stdlib.h>

void MPI_Mat_vect_read_file(const char *filename,
                            double **local_mat, 
                            double **vect, 
                            int *local_rows,
                            int *rows,
                            int *cols)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // assume both the matrix and the vector are input from a data file.
    double *mat;
    if (rank == 0)
    {
        Mat_vect_read_file("data.txt", &mat, vect, rows, cols);
    }

    MPI_Mat_vect_scatter_row(mat, local_mat, vect, local_rows, rows, cols);

    // Clean up
    if (rank == 0)
    {
        free(mat);
    }
}