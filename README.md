# Optimization of checkmate-in-N moves algorithm

## Sources

- https://github.com/asheptunov/chesslib (CPP, not used)
- https://github.com/kz04px/libchess (CPP, used)
- https://github.com/bhlangonijr/chesslib (JAVA)
- https://informatika.stei.itb.ac.id/~rinaldi.munir/Stmik/2019-2020/Makalah/stima2020k3-003.pdf (SEQUENTIAL ALGORITHM)

## Build Prerequisites (JAVA SEQUENTIAL)
- Java
- Maven

## Build Prerequisites (CPP)
- TBB (follow the commands in the root directory)
```
wget https://github.com/oneapi-src/oneTBB/releases/download/v2021.8.0/oneapi-tbb-2021.8.0-lin.tgz
tar -xvzf oneapi-tbb-2021.8.0-lin.tgz
```
- Before compiling the code, load GCC 11.2.0 and TBB first
```
module load gcc-11.2.0 && source oneapi-tbb-2021.8.0/env/vars.sh
```
- The code was only tested on linux environmnet (sunlab)

## Run
- To run the code you can just build it using the makefile and running the executable
```
make
./main
```
