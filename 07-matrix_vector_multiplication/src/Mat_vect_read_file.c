#include "Mat_vect_read_file.h"
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

void Mat_vect_read_file(const char *filename, 
                        double **mat, 
                        double **vect,
                        int *rows, 
                        int *cols)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Read the number of rows and columns
    fscanf(file, "%d %d", rows, cols);

    // Allocate memory for the matrix and vector
    *mat = (double *)malloc((*rows) * (*cols) * sizeof(double));
    *vect = (double *)malloc((*cols) * sizeof(double));

    // Read the matrix
    for (int row = 0; row < (*rows); row++)
    {
        for (int col = 0; col < (*cols); col++)
        {
            fscanf(file, "%lf", &(*mat)[row * (*cols) + col]);
        }
    }

    // Read the vector
    for (int col = 0; col < (*cols); col++)
    {
        fscanf(file, "%lf", &(*vect)[col]);
    }

    fclose(file);
}