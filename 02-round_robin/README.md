# What is this?

[![Watch the video](https://img.youtube.com/vi/c0C9mQaxsD4/hqdefault.jpg)](https://youtu.be/c0C9mQaxsD4)

# How to use?

## How to build?

```
chmod +x build.sh
./build.sh
```

## How to run?
mpirun -np 4 ./build/main > ./build/output.txt

## How to verify?
sort --numeric-sort --stable ./build/output.txt