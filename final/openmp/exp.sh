#!/bin/bash


for i in {1..20}
do
  echo $i
  ./seq < data_500k.csv | tail -n 1 >> seq_perf.dat
  ./par < data_500k.csv | tail -n 1 >> par_perf.dat
done  
