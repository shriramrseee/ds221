CC=gcc

iter=100
threads=16
size=20000
chunksize=1250

all: seq par

seq: seq.c
	$(CC) -std=c99 -DSIZE=$(size) -DITER=$(iter) -o seq seq.c

par: par.c
	$(CC) -std=c99 -fopenmp -DSIZE=$(size) -DITER=$(iter) -DTHREADS=$(threads) -DCHUNKSIZE=$(chunksize) -o par par.c

clean:
	rm -f seq par

