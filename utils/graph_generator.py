#!/usr/bin/env python
################################################################################
## Generate an undirected graph of N nodes
## range of costs for each edge (1,1000)
## max branching factor of M
################################################################################
import sys
import json
from random import randint

# python data_generator <output_path> <dimension> <max_branching>

def help_me():
   print "USAGE"
   print "\t python "+sys.argv[0]+" <output_path>  <dimension>  <max_branching>"
   print "\t Example:"
   print "\t\t python "+sys.argv[0]+" ../data/  100  4"
   print "INFO"
   print "\tGenerates an undirected graph (doubly directed) as a strongly connected component with <dimension> nodes and maximum branching factor of <max_branching>\n"

def generate_data(dimension, branching):
   real_dimension=dimension
   real_branching=branching
   topology = {}
   costs = {}
   prev = ""
   first = ""
   for i in range(0, dimension):
      if(first == ""):
         first = str(i)
      topology[str(i)] = []
      costs[str(i)] = []
      if(prev != ""):
         # doubly connect (undirected graph)
         topology[str(i)] = [prev]
         topology[prev].append(str(i))
         # doubly assign also the weights
         cost=int(randint(1, 1000))
         costs[str(i)] = [cost]
         costs[prev].append(cost)
      prev=str(i)
   # connect also the last node
   topology[first].append(prev)
   topology[prev].append(first)
   # assign weights
   cost=int(randint(1, 1000))
   costs[first].append(cost)
   costs[prev].append(cost)
   # count the connection already created
   branching=branching-1
   # eventually add other connections
   for k,v in topology.iteritems():
      number_of_tries = int(randint(1, branching))
      for i in range(1, number_of_tries):
         new_neigh = str(randint(1, int(dimension)-1))
         # do not generate a loop
         while(k == new_neigh):
            new_neigh = str(randint(1, int(dimension)-1))
         # check that the neigh is not in the current adjacency list
         if not new_neigh in topology[k]:
            topology[k].append(new_neigh)
            topology[new_neigh].append(k)
            cost=int(randint(1, 1000))
            costs[k].append(cost)
            costs[new_neigh].append(cost)
   return (topology, costs, real_dimension, real_branching)

def write_data(data):
   topology=data[0]
   costs=data[1]
   dimension=data[2]
   branching=data[3]
   out_path=str(sys.argv[1])
   with open(out_path+str(dimension)+"-"+str(branching)+"-topology.json", "w+")\
    as outfile:
      json.dump(topology, outfile, indent=4)
   with open(out_path+str(dimension)+"-"+str(branching)+"-costs.json", "w+") \
    as outfile:
      json.dump(costs, outfile, indent=4)

if(len(sys.argv) != 4):
   help_me()
   raise ValueError('Invalid parameters')

write_data(generate_data(int(sys.argv[2]), int(sys.argv[3])))