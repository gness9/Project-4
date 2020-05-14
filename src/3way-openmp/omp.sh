#!/bin/bash -l

for i in 1000
do
	for j in 1
	do
		//usr/bin/time -o $i/$j-core/time-$RANDOM.txtgcc -fopenmp $i/$j-core/omp.c -o $i/$j-core/a.out
		./$i/$j-core/a.out
	done
done