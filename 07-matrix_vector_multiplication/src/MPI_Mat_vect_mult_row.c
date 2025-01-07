#include "MPI_Mat_vect_mult_row.h"
#include <stdlib.h>

void MPI_Mat_vect_mult_row(const double *local_mat, 
                           const double *vect, 
                           double **result_vect,
                           const int local_rows,
                           const int rows,
                           const int cols,
                           MPI_Comm comm)
{
    // Perform the matrix-vector multiplication
    double *local_result = (double *)malloc(local_rows * sizeof(double));
    for (int i = 0; i < local_rows; i++) {
        local_result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            local_result[i] += local_mat[i * cols + j] * vect[j];
        }
    }

    // Cases
    // Case 1: rows < size
    // Suppose the matrix is 3x4 and the size is 4
    // recvcounts = {1, 1, 1, 0}
    // displs_result = {0, 1, 2, 3}
    //
    // Case 2: rows = size
    // Suppose the matrix is 3x4 and the size is 3
    // recvcounts = {1, 1, 1}
    // displs_result = {0, 1, 2}
    //
    // Case 3: rows > size
    // Suppose the matrix is 3x4 and the size is 2
    // recvcounts = {2, 1}
    // displs_result = {0, 2}
    int size;
    MPI_Comm_size(comm, &size);
    int *recvcounts = (int *)malloc(size * sizeof(int));
    int *displs_result = (int *)malloc(size * sizeof(int));
    int remainder = rows % size;
    int offset = 0;
    // think of i as the rank
    for (int i = 0; i < size; i++) {
        recvcounts[i] = rows / size;
        if (i < remainder) {
            recvcounts[i]++;
        }
        displs_result[i] = offset;
        offset += recvcounts[i];
    }

    // the result vector c should be distributed among the processes as blocks.
    *result_vect = (double *)malloc(rows * sizeof(double));
    MPI_Allgatherv(local_result, local_rows, MPI_DOUBLE,
                   *result_vect, recvcounts, displs_result, MPI_DOUBLE,
                   comm);

    // Clean up
    free(local_result);
    free(recvcounts);
    free(displs_result);
}