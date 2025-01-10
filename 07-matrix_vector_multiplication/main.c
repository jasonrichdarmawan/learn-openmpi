// (1) Write a matrix-vector multiplication program 
// in which matrices are distributed among the processes in block-row fashion 
// and vectors are distributed among the processes as blocks. 
// You may assume both the matrix and the vector are input from a data file. 
// At the end of the program's execution, 
// the result vector c should be distributed among the processes as blocks.

#include "Mat_vect_read_file.h"
#include "Mat_vect_create.h"
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
        // Mat_vect_read_file("data.txt", &mat, &vect, &rows, &cols);
        rows = 8;
        cols = 1e6;
        srand(0);
        Mat_vect_create(&mat, &vect, rows, cols);
    }

    // Print the matrix
    // if (rank == 0)
    // {
    //     printf("%d | Matrix:\n", rank);
    //     for (int i = 0; i < rows; i++)
    //     {
    //         printf("%d | ", rank);
    //         for (int j = 0; j < cols; j++)
    //         {
    //             printf("%.1f ", mat[i * cols + j]);
    //         }
    //         printf("\n");
    //     }
    // }

    // use optimal number of processes
    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm newcomm = MPI_COMM_NULL;
    int color = (rank < rows) ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &newcomm);
    if (newcomm == MPI_COMM_NULL)
    {
        MPI_Finalize();
        return 0;
    }

    // Start timing
    MPI_Barrier(newcomm);
    double start_time = MPI_Wtime();

    double *local_mat;
    int local_rows;
    MPI_Mat_vect_scatter_row(mat, 
                             &local_mat, 
                             &vect, 
                             &local_rows, 
                             &rows, 
                             &cols, 
                             newcomm);

    double *result_vect;
    MPI_Mat_vect_mult_row(local_mat,
                          vect, 
                          &result_vect, 
                          local_rows, 
                          rows,
                          cols,
                          newcomm);

    // End timing
    MPI_Barrier(newcomm);
    double end_time = MPI_Wtime();
    if (rank == 0)
    {
        double elapsed_time = end_time - start_time;
        printf("Elapsed time: %.0f µs\n", elapsed_time * 1e6);
    }

    // Print the result vector
    // printf("%d | Result vector: ", rank);
    // for (int i = 0; i < rows; i++)
    // {
    //     printf("%.1f ", result_vect[i]);
    // }
    // printf("\n");

    // Clean up
    if (rank == 0)
    {
        free(mat);
    }
    free(local_mat);
    free(vect);
    free(result_vect);

    MPI_Comm_free(&newcomm);

    MPI_Finalize();
    return 0;
}