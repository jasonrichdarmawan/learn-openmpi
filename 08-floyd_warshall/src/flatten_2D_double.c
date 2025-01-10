#include "flatten_2D_double.h"
#include <stdlib.h>

void flatten_2D_double(const double * const *input, double **output, const int size)
{
    *output = (double *)malloc(size * size * sizeof(double));
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            (*output)[row * size + col] = input[row][col];
        }
    }
}