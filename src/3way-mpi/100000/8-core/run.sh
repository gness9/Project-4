#!/bin/bash -l

for i in 1 2 3 4 5
do
	//usr/bin/time -o /homes/zaybrunson/proj4/src/3way-mpi/100000/8-core/time-$i.txt gcc -o /homes/zaybrunson/proj4/src/3way-mpi/100000/8-core/output-$i.out -fopenmp /homes/zaybrunson/proj4/src/3way-mpi/100000/8-core/mpi.c && /homes/zaybrunson/proj4/src/3way-mpi/100000/8-core/output-$i.out
done
