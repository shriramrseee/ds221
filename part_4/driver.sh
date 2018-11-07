#!/bin/bash

echo "Starting spark job for "$1;

spark-submit --master yarn --deploy-mode cluster --queue default --num-executors 4 --executor-cores 3 --executor-memory 9G  $1;

echo "Collecting Job logs";

# yarn logs --applicationId application_1524406905265_3036 
