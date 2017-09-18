#!/bin/bash

# substring to remove
to_remove=${1:-}

function help
{
   echo "Usage: $0 <substring to remove>"
   echo "   example: $0 -3"
}

if [ -z ${to_remove} ];
then
   echo "[ERROR: missing argument]"
   help
   exit 1
fi

directory=$(echo $to_remove | cut -d'-' -f 2)

cd ../times/results/
files=($(ls $directory))
cd $directory

for f in "${files[@]}"
do
   sed -i "s/$to_remove//g" $f
done