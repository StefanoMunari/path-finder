# Path Finder

A simple path-finder library for all kinds of maps (also not grid-based) written in C++ based on [aima](http://aima.cs.berkeley.edu/) algorithms.    

Project for the  [Artificial Intelligence course 2016/2017](http://informatica.math.unipd.it/laureamagistrale/intelligenzaartificialeen.html)   
[University of Padua - MSc Level](http://informatica.math.unipd.it/laureamagistrale/indexen.html)    

## Dependencies

* [Boost Library](http://www.boost.org/)

* [JSONCpp Library](https://en.wikiversity.org/wiki/JsonCpp)

### Uninformed Search (Algorithms)

* Greedy

* Uniform Cost

### Informed-Search (Algorithms)

* A\*


## Project structure

* bin/

contains the executables

* config/

contains the files related to docker. Useful to instantiate the entire project
without having to install all the dependencies in your local machine.

* data/

contains the graph files. For each graph 2 json files are necessary:
1. one specifies the connection through an adjacency list (*-topology.json)  
2. one specifies the costs through an adjacency list (*-costs.json)


* doc/

contains the documentation of the project generated using doxygen

run the following command from the root of the project:

```bash
doxygen
```

* etc/

contains the configuration files for _main.cc_ and _times.cc_

* obj/

contains object files generated with make

* src/

contains the source files divided by bindings related sources and core sources

* times/

contains the sources necessary to measure the time performances of the
algorithms. It also contains two folders: one will be used to store the results,
the other will be used by the statistics script to extract statistics from the
results

* utils/

contains scripts to generate graphs and statistics based on times.cc results.
It contains also a runner to automatically execute sets of performance tests.

## Usage
