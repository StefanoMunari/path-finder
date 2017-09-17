#!/bin/bash
## run the time measurements

cd ..
make clean
# compile times
make times OPT=times mode=/core
# run 100 simulations
for i in $(seq 1 100);
do
   ./bin/find_path
done