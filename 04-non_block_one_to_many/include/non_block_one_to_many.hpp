#ifndef NON_BLOCK_ONE_TO_MANY
#define NON_BLOCK_ONE_TO_MANY

#include <mpi.h>

void await_request(int rank, MPI_Request *request);
void receive_from_one(int rank);
void send_to_many(int num_procs);

#endif // NON_BLOCK_ONE_TO_MANY