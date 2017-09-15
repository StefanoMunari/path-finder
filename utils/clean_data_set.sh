#!/bin/bash

cd ../times/
files=($(ls ready))
cd ready

for f in "${files[@]}"
do
   sed -i "s/-3//g" $f
done

cd ..
files=($(ls results))
cd results
for f in "${files[@]}"
do
   sed -i "s/-9//g" $f
done