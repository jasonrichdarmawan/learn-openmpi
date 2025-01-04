#include <mpi.h>
#include "helpers.hpp"
#include "non_block_one_to_many.hpp"

int main(int argc, char **argv)
{
    int num_procs;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    start_timer();
    
    debug(rank, "HELLO (p=%d)\n", num_procs);
    if (rank == 0) {
        send_to_many(num_procs);
    } else {
        receive_from_one(rank);
    }
    debug(rank, "GOODBYE\n");

    MPI_Finalize();
    return 0;
}
