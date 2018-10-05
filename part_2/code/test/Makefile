CC=g++

all: mat_gen.o bfs_gen.o

mat_gen.o: mat_gen.cpp
	$(CC) -std=c++11 mat_gen.cpp -o mat_gen.o

bfs_gen.o: bfs_gen.cpp
	$(CC) -std=c++11 bfs_gen.cpp -o bfs_gen.o

clean:
	rm -rf mat_gen.o bfs_gen.o input.tsv output.tsv tmp
