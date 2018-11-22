CC=gcc

iter=100
threads=16
size=20000
chunksize=1250

all: seq par

seq: seq.c
	$(CC) -DSIZE=$(size) -DITER=$(iter) -o seq seq.c

par: par.c
	$(CC) -fopenmp -DSIZE=$(size) -DITER=$(iter) -DTHREADS=$(threads) -DCHUNKSIZE=$(chunksize) -o par par.c

clean:
	rm -f seq par

