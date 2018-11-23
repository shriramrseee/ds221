#!/bin/bash


for i in {1..20}
do
  echo $i
  ./seq < merge_data.txt > data.out
  tail -n 1 data.out >> seq_perf.dat
  ./par < merge_data.txt > data.out
  tail -n 1 data.out >> par_perf.dat
done  
