#!/bin/bash


#sbatch --constrain=elves --time=00:10:00 --ntasks-per-node=1 --nodes=1 --mem-per-cpu=124M ./1000/1-core/run.sh

#for k in 1 #2 3 4 5
#do
	for i in 1000 #10000 100000 1000000
	do
		for j in 1 #2 4 8 16
		do
			#. $i/$j-core/run.sh
			#sbatch --constrain=elves --time=00:10:00 --ntasks-per-node=$j --nodes=1 --mem-per-cpu=124m //usr/bin/time -o $i/$j-core/time-$k.txt gcc -o $i/$j-core/a.out -fopenmp $i/$j-core/omp.c  && ./$i/$j-core/a.out
			#sbatch --constrain=elves --time=00:10:00 --ntasks-per-node=$j --nodes=1 --mem-per-cpu=124m gcc -fopenmp $i/$j-core/omp.c
			sbatch --constrain=elves --time=00:10:00 --ntasks-per-node=$j --nodes=1 --mem-per-cpu=$((8/$j))G $i/$j-core/run.sh
			#//usr/bin/time -o $i/$j-core/time-$k.txt gcc -o $i/$j-core/a.out -fopenmp $i/$j-core/omp.c && ./$i/$j-core/a.out
			#./$i/$j-core/a.out
		done
	done
#done
