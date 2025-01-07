// (1) Write a matrix-vector multiplication program 
// in which matrices are distributed among the processes in block-row fashion 
// and vectors are distributed among the processes as blocks. 
// You may assume both the matrix and the vector are input from a data file. 
// At the end of the program's execution, 
// the result vector c should be distributed among the processes as blocks.

#include "Mat_vect_read_file.h"
#include "MPI_Mat_vect_mult_row.h"
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    // assume both the matrix and the vector are input from a data file.
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