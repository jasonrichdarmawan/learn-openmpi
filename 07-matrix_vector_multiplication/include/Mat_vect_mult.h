#ifndef MAT_VECT_MULT_H
#define MAT_VECT_MULT_H

// mat * vect = result_vect
void Mat_vect_mult(const double *mat,
                   const double *vect,
                   double *result_vect,
                   const int rows,
                   const int cols);

#endif // MAT_VECT_MULT_H