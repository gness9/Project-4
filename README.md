# Project-4
Final CIS520 Project
# What we have to do for performance analysis:
Cores: 1, 2, 4, 8, 32
Data Sizes: 100, 10000, 100000, 1 million
## Things to track
- The above
- CPU Utilization
- RAM Usage
- All across the different parallelization techniques

This link may help us: https://k-state.instructure.com/courses/85470/files/folder/Projects?preview=12576314

Figured out how to get stats:
commands to run:
- export TIME="time result\ncmd: %C\nreal: %es\nuser: %Us \nsys: %Ss \nmemory: %MKB \ncpu: %P"
- /usr/bin/time -o test.txt sbatch ./[scheduled batch script]
yes the cpu usage goes over 100%... idk why but it does.
