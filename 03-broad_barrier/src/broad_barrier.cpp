#include "broad_barrier.hpp"
#include <time.h>
#include <cstdlib>
#include <helpers.hpp>
#include <mpi.h>
#include <unistd.h>

long broadcast(int rank, int num_procs)
{
    long random_value;
    int broadcaster_rank = 0;

    if (rank == broadcaster_rank) {
        srandom(time(NULL) + rank);
        random_value = random() / (RAND_MAX / 10);
        debug(rank, "broadcasting %ld\n", random_value);
    }

    MPI_Bcast((void *)&random_value, 1, MPI_LONG, broadcaster_rank, MPI_COMM_WORLD);

    if (rank != broadcaster_rank) {
        debug(rank, "received %ld\n", random_value);
    }

    return random_value;
}

void barrier(int rank, long random_value)
{
    int nap_time = random_value + (2 * rank);
    debug(rank, "sleeping for %ds\n", nap_time);
    sleep(nap_time);

    debug(rank, "enter b-a-r-r-i-e-r\n");
    MPI_Barrier(MPI_COMM_WORLD);
    debug(rank, "leave barrier\n");
}