#!/bin/bash

cap=$1
n=$2

while [ $n -lt $3 ]
do
  ../Runner.o 'hash' $cap input$n.tsv lookup$n.tsv out$n.tsv
  n=$(($n * 10))
done 
