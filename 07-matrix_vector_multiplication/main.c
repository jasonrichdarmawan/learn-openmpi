// (1) Write a matrix-vector multiplication program 
// in which matrices are distributed among the processes in block-row fashion 
// and vectors are distributed among the processes as blocks. 
// You may assume both the matrix and the vector are input from a data file. 
// At the end of the program's execution, 
// the result vector c should be distributed among the processes as blocks.

#include "Mat_vect_read_file.h"
#include "Mat_vect_mult.h"
#include <stdio.h>

#include <mpi.h>
#include <stdlib.h>

// mat * vect = result_vect
// matrices are distributed among the process in block-row fashion
// vectors are distributed among the processes as blocks
// the result vector c should be distributed among the processes as blocks
// the shortcoming of this approach is that the number of processes should be equal or greater to the number of rows
void MPI_Mat_vect_mult_row(const double *mat, 
                           const double *vect,
                           double **result_vect,
                           const int rows,
                           const int cols);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    double *mat, *vect;
    int rows, cols;
    Mat_vect_read_file("data.txt", &mat, &vect, &rows, &cols);

    double *result_vect;
    MPI_Mat_vect_mult_row(mat, vect, &result_vect, rows, cols);

    // Print the result vector
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%d | Result vector: ", rank);
    for (int i = 0; i < rows; i++)
    {
        printf("%.1f ", result_vect[i]);
    }
    printf("\n");

    // Clean up
    free(mat);
    free(vect);
    free(result_vect);

    MPI_Finalize();
    return 0;
}

void MPI_Mat_vect_mult_row(const double *mat, 
                           const double *vect, 
                           double **result_vect,
                           const int rows,
                           const int cols)
{
    *result_vect = (double *)malloc(rows * sizeof(double));

    // matrices are distributed among the process in block-row fashion
    double local_mat[cols];
    MPI_Scatter(mat, cols, MPI_DOUBLE,
                local_mat, cols, MPI_DOUBLE,
                0,
                MPI_COMM_WORLD);
    
    // vectors are distributed among the processes as blocks
    MPI_Bcast(vect, cols, MPI_DOUBLE,
              0,
              MPI_COMM_WORLD);

    // Perform the matrix-vector multiplication
    double local_result = 0.0;
    for (int col = 0; col < cols; col++)
    {
        local_result += local_mat[col] * vect[col];
    }

    // the result vector c should be distributed among the processes as blocks.
    MPI_Allgather(&local_result, 1, MPI_DOUBLE,
                  *result_vect, 1, MPI_DOUBLE, MPI_COMM_WORLD);
}