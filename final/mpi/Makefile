CC=gcc
MPICC=mpicc

size=100000
procs=4

all: seq par

seq: seq.c
	$(CC) -Wall -DSIZE=$(size) -o seq seq.c

par: par.c
	$(MPICC) -Wall -DSIZE=$(size) -o par par.c

clean:
	rm -f seq par

