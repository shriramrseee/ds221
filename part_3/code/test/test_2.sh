#!/bin/bash

t=$1
n=$2

while [ $n -lt $3 ]
do
  ../Runner.o $t $n input$n.tsv lookup$n.tsv out$n.tsv
  n=$(($n * 10))
done 
