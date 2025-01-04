# What is this?

## broad_barrier: Collective Communication

[![Watch the video](https://img.youtube.com/vi/q9OfXis50Rg/hqdefault.jpg)](https://www.youtu.be/q9OfXis50Rg)

# How to use?

## How to build?

```
chmod +x build.sh
```

### without busy wait

usage: to demonstrate if the receiver read the buffer before receiving the data from the sender, the buffer value will be wrong.

```
./build.sh
```

### with busy wait

```
./build.sh -b
```

## How to run?

### non_block_one_to_many

```
mpirun -np 4 ./build/main > ./build/output.txt
```

## How to verify?

```
sort --numeric-sort --stable ./build/output.txt
```