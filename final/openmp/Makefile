CC=gcc

iter=100
threads=16
size=500000
chunksize=31250
schedule=dynamic

all: seq par

seq: seq.c
	$(CC) -std=c99 -DSIZE=$(size) -DITER=$(iter) -o seq seq.c

par: par.c
	$(CC) -std=c99 -fopenmp -DSIZE=$(size) -DITER=$(iter) -DTHREADS=$(threads) -DCHUNKSIZE=$(chunksize) -DSCHEDULE=$(schedule) -o par par.c

clean:
	rm -f seq par

