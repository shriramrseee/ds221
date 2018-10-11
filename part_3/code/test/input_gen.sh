#!/bin/bash

n=$1

while [ $n -lt $2 ]
do
  echo $n | ./input_gen.o > input$n.tsv
  cat input$n.tsv | awk '{print $1}' > lookup$n.tsv
  n=$(($n * 10))
done 
