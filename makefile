cc=gcc
args=-DSIZE=1024
flags=-O2 -ftree-vectorize -fopt-info-vec-optimized

all: mm_cache_vec mm_naive_vec mm_cache_no_vec mm_naive_no_vec

mm_cache_vec:
	$(cc) $(args) $(flags) -o mm_cache_vec mm_cache.c

mm_naive_vec:
	$(cc) $(args) $(flags) -o mm_naive_vec mm_naive.c

mm_cache_no_vec:
	$(cc) $(args) -o mm_cache_no_vec mm_cache.c

mm_naive_no_vec:
	$(cc) $(args) -o mm_naive_no_vec mm_naive.c

clean:
	rm mm_cache_vec mm_naive_vec mm_cache_no_vec mm_naive_no_vec
