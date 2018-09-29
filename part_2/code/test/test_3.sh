#!/bin/bash

n=$1

while [ $n -lt $2 ]
do
  echo $n $3 | ./mat_gen.o > input1.tsv
  echo $n $3 | ./mat_gen.o > input2.tsv
  ../Runner.o multiply $4 input1.tsv input2.tsv output.tsv
  n=$(($n * 2))
done 
