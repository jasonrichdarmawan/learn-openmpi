#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    int num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // This function indicates the number of processes involved in a communicator. 
    // For MPI_COMM_WORLD, it indicates the total number of processes available
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Do many things, all at once
    printf("Hello: rank %d, num_procs: %d\n", rank, num_procs);
    
    MPI_Finalize();
    return 0;
}