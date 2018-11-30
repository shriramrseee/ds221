CC=gcc
MPICC=mpicc

size=100000

all: seq par

seq: seq.c
	$(CC) -std=c99 -DSIZE=$(size) -o seq seq.c

par: par.c
	$(MPICC) -std=c99 -DSIZE=$(size) -o par par.c

clean:
	rm -f seq par

