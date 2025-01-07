# What is this?

(1) Write a matrix-vector multiplication program 
in which matrices are distributed among the processes in block-row fashion 
and vectors are distributed among the processes as blocks. 
You may assume both the matrix and the vector are input from a data file. 
At the end of the program's execution, 
the result vector c should be distributed among the processes as blocks.

The idea are:
1. `MPI_Scatterv` to scatter matrices in varying sizes depending on the number of processes
2. `MPI_Allgatherv` to gather local matrices in varying sizes from each process and distributed to all process

# How to build?

```
chmod +x build.sh
./build.sh
```

# How to use?

```
mpirun -np <number of processes> ./build/main
```