# What is this?

## broad_barrier: Collective Communication

[![Watch the video](https://img.youtube.com/vi/q9OfXis50Rg/hqdefault.jpg)](https://www.youtu.be/q9OfXis50Rg)

# How to use?

## How to build?

```
chmod +x build.sh
```

### print map

```
./build.sh -m
```

### print neighbors

```
./build.sh -n
```

## How to run?

```
mpirun -np 4 ./build/main > ./build/output.txt
```

## How to verify?

```
sort --numeric-sort --stable ./build/output.txt
```