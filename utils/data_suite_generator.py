#!/usr/bin/env python

import sys
import os

if(len(sys.argv) != 6):
   raise ValueError('Invalid parameters')

out_path=str(sys.argv[1])
start=int(sys.argv[2])
to=int(sys.argv[3])
step=int(sys.argv[4])
branching=int(sys.argv[5])
data=[]
it=1
value=start

while(value < to):
   data.append(value)
   value=value*step**it
   it=it+1

data=[]

data=[500, 1000, 1500, 2500, 3500, 4500, 5500, 7000, 8000, 10000, 30000, 50000, 70000, 85000,  100000]

for d in data:
   os.system("python graph_generator.py "+out_path+" "+str(d)+" "+str(branching))