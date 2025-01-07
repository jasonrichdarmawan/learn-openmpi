#include "MPI_Mat_vect_scatter_row.h"
#include <mpi.h>
#include <stdlib.h>

void MPI_Mat_vect_scatter_row(const double *mat,
                              double **local_mat,
                              double **vect,
                              int *local_rows,
                              const int *rows,
                              const int *cols)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Bcast((void *)rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    *local_rows = (*rows) / size;
    int remainder = (*rows) % size;
    if (rank < remainder) {
        (*local_rows)++;
    }

    MPI_Bcast((void *)cols, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int *sendcounts = (int *)malloc(size * sizeof(int));
    int *displs = (int *)malloc(size * sizeof(int));
    int offset = 0;
    // think of i as the rank
    for (int i = 0; i < size; i++) {
        sendcounts[i] = ((*rows) / size) * (*cols);
        if (i < remainder) {
            sendcounts[i] += (*cols);
        }
        displs[i] = offset;
        offset += sendcounts[i];
    }

    // matrices are distributed among the processes in block-row fashion
    *local_mat = (double *)malloc((*local_rows) * (*cols) * sizeof(double));
    MPI_Scatterv(mat, sendcounts, displs, MPI_DOUBLE,
                 *local_mat, (*local_rows) * (*cols), MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    // vectors are distributed among the processes as blocks
    if (rank != 0)
    {
        *vect = (double *)malloc((*cols) * sizeof(double));
    }
    MPI_Bcast(*vect, *cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Clean up
    free(sendcounts);
    free(displs);
}