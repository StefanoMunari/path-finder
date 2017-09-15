#!/bin/bash
## run the time measurements

cd ..
make clean
make times OPT=times mode=/core
for i in $(seq 1 20);
do
   ./bin/find_path &
   sleep 100s;
done