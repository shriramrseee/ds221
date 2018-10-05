#!/bin/bash

echo "Running Load test"

../Runner.o load array small.tsv output1.tsv
../Runner.o load csr small.tsv output2.tsv
cmp output1.tsv output2.tsv

echo "Running Add test"

../Runner.o add array small.tsv small.tsv output1.tsv
../Runner.o add csr small.tsv small.tsv output2.tsv
cmp output1.tsv output2.tsv

echo "Running multiply test"

../Runner.o multiply array small.tsv small.tsv output1.tsv
../Runner.o multiply csr small.tsv small.tsv output2.tsv
cmp output1.tsv output2.tsv

echo "Running BFS test"

../Runner.o bfs small.tsv 0 output.tsv



 
