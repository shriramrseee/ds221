CC=gcc

iter=10
threads=8
chunksize=2500

all: seq par

seq: seq.c
	$(CC) -Wall -DITER=$(iter) -o seq seq.c

par: par.c
	$(CC) -Wall -fopenmp -DITER=$(iter) -DTHREADS=$(threads) -DCHUNKSIZE=$(chunksize) -o par par.c

clean:
	rm -f seq par

