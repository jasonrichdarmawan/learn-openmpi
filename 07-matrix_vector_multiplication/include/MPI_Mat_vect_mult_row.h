#ifndef MPI_MAT_VECT_MULT_ROW_H
#define MPI_MAT_VECT_MULT_ROW_H

// mat * vect = result_vect
// matrices are distributed among the process in block-row fashion
// vectors are distributed among the processes as blocks
// the result vector c should be distributed among the processes as blocks
void MPI_Mat_vect_mult_row(const double *mat, 
                           const double *vect, 
                           double **result_vect,
                           const int rows,
                           const int cols);

#endif // MPI_MAT_VECT_MULT_ROW_H