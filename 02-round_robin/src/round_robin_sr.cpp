#include "round_robin.hpp"
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>

/**
 * ◜1◝
 * 0 2
 * ◟3◞
 */
void round_robin(int rank, int num_procs)
{
    long int rand_mine, rand_prev;
    int rank_next = (rank + 1) % num_procs;
    int rank_prev = rank == 0 ? num_procs - 1 : rank - 1;
    MPI_Status status;

    srandom(time(NULL) + rank);
    rand_mine = random() / (RAND_MAX / 100);
    printf("%d: random is %ld\n", rank, rand_mine);

    // The idea:
    // Organize the calling of those send and receive functions
    // in such a way that when one process is sending to another 
    // that other process is listening to the firt
    // So, we're essentially dividing the processes into two groups
    // ones that are going to send first and then receive
    // and ones that are going to receive first and then send
    // ◜1◝
    // 0 2
    // ◟3◞
    MPI_Sendrecv((void *)&rand_mine, 1, MPI_LONG, rank_next, 1,
                 (void *)&rand_prev, 1, MPI_LONG, rank_prev, 1,
                 MPI_COMM_WORLD, &status);

    printf("%d: I had %ld, %d had %ld\n", rank, rand_mine, rank_prev, rand_prev);
}