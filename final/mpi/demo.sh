#!/bin/bash


for i in {1..5}
do
  echo $i
  ./seq < merge_data.txt > seq_data.out
  tail -n 1 data.out >> seq_perf.dat
  mpiexec -np $1 -f $PBS_NODEFILE ./par merge_data.txt > par_data.out
  tail -n 1 data.out >> par_perf.dat
done  
