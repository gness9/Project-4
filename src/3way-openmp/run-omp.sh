#!/bin/bash

for i in 1000 10000 100000 1000000
do
	echo "{$i} lines"
        for k in 1 2 4 8 16
        do
		echo "{$k} cores"
                sbatch --constraint=elves --time=00:10:00 --nodes=1 --ntasks-per-node=$k --mem-per-cpu=124M --output $i/$k-core/slurm-%j.out $i/$k-core/run.sh 
        done
done


