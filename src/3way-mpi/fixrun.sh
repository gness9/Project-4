#!/bin/bash

for i in 1000 10000 100000 1000000
do
#	echo "{$i} lines"
        for k in 1 2 4 8 16
        do
#		echo "{$k} cores"
                dos2unix $i/$k-core/run.sh 
        done
done


