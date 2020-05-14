#!/bin/bash -l

for i in 1 2 3 4 5
do
	//usr/bin/time -o /homes/zaybrunson/proj4/src/3way-openmp/1000/2-core/time-$i.txt gcc -o /homes/zaybrunson/proj4/src/3way-openmp/1000/2-core/output-$i.out -fopenmp /homes/zaybrunson/proj4/src/3way-openmp/1000/2-core/omp.c && /homes/zaybrunson/proj4/src/3way-openmp/1000/2-core/output-$i.out
done
