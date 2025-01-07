#ifndef MAT_VECT_READ_FILE_H
#define MAT_VECT_READ_FILE_H

// Suppose the matrix is 3x4 and the vector is 4x1
// The file should look like this:
// rows cols
// mat_00 mat_01 mat_02 mat_03
// mat_10 mat_11 mat_12 mat_13
// mat_20 mat_21 mat_22 mat_23
// vect_0 vect_1 vect_2 vect_3
void Mat_vect_read_file(const char *filename,
                        double **mat, 
                        double **vect,
                        int *rows, 
                        int *cols);

#endif // MAT_VECT_READ_FILE_H