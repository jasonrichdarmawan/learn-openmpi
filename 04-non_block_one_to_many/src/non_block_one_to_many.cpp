#include <stdlib.h>
#include "helpers.hpp"
#include <mpi.h>

#ifndef BUSY_WAIT
#define BUSY_WAIT 1
#endif

// Alternatively you can use MPI_Wait
// This is just an example of how to use MPI_Test
void await_request(int rank, MPI_Request *request)
{
#if BUSY_WAIT
    int wait_count = 0;
    int flag = 0;
    MPI_Status status;

    do {
        wait_count++;
        MPI_Test(request, &flag, &status);
    } while (!flag);
    debug(rank, "tested %d times \n", wait_count);
#endif
}

void send_to_many(int num_procs)
{
    long rand_value = random() / (RAND_MAX / 100);
    debug(0, "random value is %ld\n", rand_value);
    MPI_Request send_request;

    for (int to_rank = 1; to_rank < num_procs; to_rank++) {
        long value_sent = rand_value + to_rank;

        MPI_Isend((void *)&value_sent, 1, MPI_LONG, 
                  to_rank, 1, MPI_COMM_WORLD, &send_request);

        await_request(0, &send_request); // MPI_Isend don't need to wait, notice "tested 1 times"
        debug(0, "sent %ld to %d\n", value_sent, to_rank);
    }
}

void receive_from_one(int rank)
{
    long recv_buffer;
    MPI_Request recv_request;

    MPI_Irecv((void *)&recv_buffer, 1, MPI_LONG, 
              0, 1, MPI_COMM_WORLD, &recv_request);

    await_request(rank, &recv_request); // MPI_Irecv need to wait, notice the difference when BUSY_WAIT is 0
    debug(rank, "got value %ld\n", recv_buffer);
}