CC=gcc
NVCC=nvcc

size=20000
threads_per_block=1000

all: seq par

par: par.cu
	$(NVCC) -DSIZE=$(size)  -DTHREADS_PER_BLOCK=$(threads_per_block) -o par par.cu

seq: seq.c
	$(CC) -std=c99 -DSIZE=$(size) -o seq seq.c

clean:
	rm -f seq par

