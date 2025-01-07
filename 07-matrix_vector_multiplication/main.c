// (1) Write a matrix-vector multiplication program 
// in which matrices are distributed among the processes in block-row fashion 
// and vectors are distributed among the processes as blocks. 
// You may assume both the matrix and the vector are input from a data file. 
// At the end of the program's execution, 
// the result vector c should be distributed among the processes as blocks.

#include "Mat_vect_read_file.h"
#include "MPI_Mat_vect_scatter_row.h"
#include "MPI_Mat_vect_mult_row.h"
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // assume both the matrix and the vector are input from a data file.
    double *mat, *vect;
    int rows, cols;
    if (rank == 0)
    {
        Mat_vect_read_file("data.txt", &mat, &vect, &rows, &cols);
    }

    double *local_mat;
    int local_rows;
    MPI_Mat_vect_scatter_row(mat, &local_mat, &vect, &local_rows, &rows, &cols);

    // Start timing
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    double *result_vect;
    MPI_Mat_vect_mult_row(local_mat,
                          vect, 
                          &result_vect, 
                          local_rows, 
                          rows,
                          cols);

    // End timing
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();
    if (rank == 0)
    {
        double elapsed_time = end_time - start_time;
        printf("Elapsed time: %.0f µs\n", elapsed_time * 1e6);
    }

    // Print the result vector
    printf("%d | Result vector: ", rank);
    for (int i = 0; i < rows; i++)
    {
        printf("%.1f ", result_vect[i]);
    }
    printf("\n");

    // Clean up
    if (rank == 0)
    {
        free(mat);
    }
    free(local_mat);
    free(vect);
    free(result_vect);

    MPI_Finalize();
    return 0;
}