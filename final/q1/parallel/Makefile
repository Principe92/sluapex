CC=g++
CFLAGS=-Wall -fopenmp -pg

all=mergesort_parallel

mergesort_serial: mergesort_parallel.cpp
	$(CC) $(CFLAGS) -o mergesort_parallel mergesort_parallel.cpp

clean:
	rm -f mergesort_parallel
