#include "MPI_Mat_vect_mult_row.h"
#include <mpi.h>
#include <stdlib.h>

void MPI_Mat_vect_mult_row(const double *mat, 
                           const double *vect, 
                           double **result_vect,
                           const int rows,
                           const int cols)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cases
    // Case 1: rows < size
    // Suppose the matrix is 3x4 and the size is 4
    // local_rows = 3 / 4 = 0
    // remainder = 3 % 4 = 3
    // rank 0: local_rows = 1
    // rank 1: local_rows = 1
    // rank 2: local_rows = 1
    // rank 3: local_rows = 0
    //
    // Case 2: rows = size
    // Suppose the matrix is 3x4 and the size is 3
    // local_rows = 3 / 3 = 1
    // remainder = 3 % 3 = 0
    // rank 0: local_rows = 1
    // rank 1: local_rows = 1
    // rank 2: local_rows = 1
    //
    // Case 3: rows > size
    // Suppose the matrix is 3x4 and the size is 2
    // local_rows = 3 / 2 = 1
    // remainder = 3 % 2 = 1
    // rank 0: local_rows = 2
    // rank 1: local_rows = 1
    int local_rows = rows / size;
    int remainder = rows % size;
    if (rank < remainder) {
        local_rows++;
    }

    // Cases
    // Case 1: rows < size
    // Suppose the matrix is 3x4 and the size is 4
    // rank 0: local_mat = 1x4; local_result = 1
    // rank 1: local_mat = 1x4; local_result = 1
    // rank 2: local_mat = 1x4; local_result = 1
    // rank 3: local_mat = 0x4; local_result = 0
    //
    // Case 2: rows = size
    // Suppose the matrix is 3x4 and the size is 3
    // rank 0: local_mat = 1x4; local_result = 1
    // rank 1: local_mat = 1x4; local_result = 1
    // rank 2: local_mat = 1x4; local_result = 1
    //
    // Case 3: rows > size
    // Suppose the matrix is 3x4 and the size is 2
    // rank 0: local_mat = 2x4; local_result = 2
    // rank 1: local_mat = 1x4; local_result = 1
    double *local_mat = (double *)malloc(local_rows * cols * sizeof(double));
    double *local_result = (double *)malloc(local_rows * sizeof(double));

    // Cases
    // Case 1: rows < size
    // Suppose the matrix is 3x4 and the size is 4
    // sendcounts = {4, 4, 4, 0}
    // displs = {0, 4, 8, 12}
    //
    // Case 2: rows = size
    // Suppose the matrix is 3x4 and the size is 3
    // sendcounts = {4, 4, 4}
    // displs = {0, 4, 8}
    //
    // Case 3: rows > size
    // Suppose the matrix is 3x4 and the size is 2
    // sendcounts = {8, 4}
    // displs = {0, 8}
    int *sendcounts = (int *)malloc(size * sizeof(int));
    int *displs = (int *)malloc(size * sizeof(int));
    int offset = 0;
    // think of i as the rank
    for (int i = 0; i < size; i++) {
        sendcounts[i] = (rows / size) * cols;
        if (i < remainder) {
            sendcounts[i] += cols;
        }
        displs[i] = offset;
        offset += sendcounts[i];
    }

    // matrices are distributed among the processes in block-row fashion
    MPI_Scatterv(mat, sendcounts, displs, MPI_DOUBLE,
                 local_mat, local_rows * cols, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    // vectors are distributed among the processes as blocks
    MPI_Bcast((void *)vect, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Perform the matrix-vector multiplication
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
    int *recvcounts = (int *)malloc(size * sizeof(int));
    int *displs_result = (int *)malloc(size * sizeof(int));
    offset = 0;
    // think of i as the rank
    for (int i = 0; i < size; i++) {
        recvcounts[i] = rows / size;
        if (i < remainder) {
            recvcounts[i]++;
        }
        displs_result[i] = offset;
        offset += recvcounts[i];
    }

    *result_vect = (double *)malloc(rows * sizeof(double));
    // the result vector c should be distributed among the processes as blocks.
    MPI_Allgatherv(local_result, local_rows, MPI_DOUBLE,
                   *result_vect, recvcounts, displs_result, MPI_DOUBLE,
                   MPI_COMM_WORLD);

    free(local_mat);
    free(local_result);
    free(sendcounts);
    free(displs);
    free(recvcounts);
    free(displs_result);
}