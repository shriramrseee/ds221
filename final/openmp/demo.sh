#!/bin/bash


for i in {1..5}
do
  echo $i
  ./seq < data_500k.csv >> seq.out
  ./par < data_500k.csv >> par.out
done  
