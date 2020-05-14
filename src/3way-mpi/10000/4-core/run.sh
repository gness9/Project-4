#!/bin/bash -l

for i in 1 2 3 4 5
do
	//usr/bin/time -o /homes/zaybrunson/proj4/src/3way-mpi/10000/4-core/time-$i.txt gcc -o /homes/zaybrunson/proj4/src/3way-mpi/10000/4-core/output-$i.out -fopenmp /homes/zaybrunson/proj4/src/3way-mpi/10000/4-core/mpi.c && /homes/zaybrunson/proj4/src/3way-mpi/10000/4-core/output-$i.out
done
