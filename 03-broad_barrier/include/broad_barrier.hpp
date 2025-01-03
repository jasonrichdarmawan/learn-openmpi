#ifndef BROAD_BARRIER
#define BROAD_BARRIER

long broadcast(int rank, int num_procs);
void barrier(int rank, long random_value);

#endif // BROAD_BARRIER