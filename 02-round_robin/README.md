# What is this?

## round_robin: Basic Send and Receive

[![Watch the video](https://img.youtube.com/vi/c0C9mQaxsD4/hqdefault.jpg)](https://youtu.be/c0C9mQaxsD4)

## round_robin_sr: Simultaneous Send-Receive

[![Watch the video](https://img.youtube.com/vi/q9OfXis50Rg/hqdefault.jpg)](https://www.youtu.be/q9OfXis50Rg)

# How to use?

## How to build?

```
chmod +x build.sh
./build.sh
```

## How to run?

### round_robin

```
mpirun -np 4 ./build/main > ./build/output.txt
```

### round_robin_sr

```
mpirun -np 4 ./build/main_sr > .build/output_sr.txt
```

## How to verify?

```
sort --numeric-sort --stable ./build/output.txt
```