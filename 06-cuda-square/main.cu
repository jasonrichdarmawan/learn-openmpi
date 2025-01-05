#include <stdio.h>
#include <cuda_runtime.h>

// __ is pronounced "dunder" (double underscore)
__global__ void square(float *d_out, float *d_in)
{
    int idx = threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = f * f;
}

int main(int argc, char **argv)
{
    const int ARRAY_SIZE = 64;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

    // Declare and initialize CPU arrays
    float h_in[ARRAY_SIZE];
    float h_out[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        h_in[i] = float(i);
    }

    // Declare and allocate GPU memory.
    float *d_in;
    float *d_out;

    cudaMalloc(
        (void **)&d_in,
        ARRAY_BYTES);   // numbers of bytes to allocate
    cudaMalloc((void **)&d_out, ARRAY_BYTES);

    // Copy array to GPU.
    cudaMemcpy(d_in,                    // reference on the cpu side to memory allocated on the gpu
               h_in,                    // reference on the cpu side
               ARRAY_BYTES,             // how many bytes to copy from h_in to d_in
               cudaMemcpyHostToDevice); // direction

    // Launch the kernel.
    square<<<1, ARRAY_SIZE>>>(d_out, d_in);

    // Copy results back from GPU.
    cudaMemcpy(h_out,                   // destination
               d_out,                   // source
               ARRAY_BYTES,             
               cudaMemcpyDeviceToHost);

    // Release GPU memory.
    cudaFree(d_in);
    cudaFree(d_out);

    // Print the results.
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%f", h_out[i]);
    }
    printf("\n");

    return 0;
}
