#!/bin/bash

n=$1

while [ $n -lt $2 ]
do
  echo $n $3 | ./mat_gen.o > input.tsv
  /usr/bin/time -f "%M" ../Runner.o load $4 input.tsv output.tsv > tmp
  n=$(($n * 2))
done 
