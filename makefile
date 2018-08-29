cc=gcc
args=-DSIZE=2048
flags=-O2 -ftree-vectorize -fopt-info-vec-optimized

all: mm_cache mm_naive

mm_cache:
	$(cc) $(args) $(flags) -o mm_cache mm_cache.c

mm_naive:
	$(cc) $(args) $(flags) -o mm_naive mm_naive.c

clean:
	rm mm_cache mm_naive
