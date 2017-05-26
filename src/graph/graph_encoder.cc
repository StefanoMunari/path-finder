/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_encoder.h"
#include <boost/graph/adjacency_list.hpp>
#include <map>
#include <vector>
#include <string>
#include <utility>

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	Graph* GraphEncoder::Encode(PyDictObject* graph_dictionary,
		PyDictObject* costs_dictionary){
		Graph* graph = nullptr;

		if(PyDict_Check(graph_dictionary) && PyDict_Check(costs_dictionary)){
			/* set up graph */
			graph = new Graph();
			/* vars */
			StringToVertexMap converter;
			vector<vector<string>> neighbors = vector<vector<string>>();
			int index =0;
			/* PyC objects */
			PyObject *keys[2], *values[2];
			Py_ssize_t positions[2] = {0};

			while(PyDict_Next((PyObject*) graph_dictionary,
				&positions[0], &keys[0], &values[0]))
			{
			  if(PyList_Check(values[0])){
					VertexDescriptor vertex_descr;
					vertex_descr = boost::add_vertex(vertex_descr,(*graph));
					(*graph)[index] = index;
					std::string vertex_id = PyString_AsString(PyObject_Str(keys[0]));
					converter.insert(
						std::pair<std::string, VertexDescriptor>(
							vertex_id, vertex_descr));
					neighbors.push_back(vector<string>());
					int size = PyList_Size(values[0]);
					for(int i =0; i < size; ++i){
						std::string neighbor_id = PyString_AsString(PyObject_Str(
							PyList_GetItem(values[0],i)));
						neighbors[index].push_back(neighbor_id);
					}
					++index;
				}
			}

			index =0;
			while(PyDict_Next((PyObject*) costs_dictionary, &positions[1],
			 	&keys[1], &values[1]))
			{
			    if(PyList_Check(values[1])){
			    	int size=neighbors[index].size();
			    	for(int i =0; i < size; ++i){
						VertexDescriptor neighbor_descr;
						VertexDescriptor source_descr;
			    		neighbor_descr = converter[neighbors[index][i]];
						source_descr = (*graph)[index];
			    		const Weight cost = ((unsigned int)
			    				PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[1],i)));
						//EdgeDescriptor edge_descr =
						boost::add_edge(source_descr,
										neighbor_descr,
										cost, (*graph)).first;
						/*
						cout<<"Index Source : "<<node_index[source_descr]<<endl;
						cout<<"Neighbor : "<<neighbors[index][i]<<
						" = > Index Neighbor: "<<node_index[neighbor_descr]<<endl;
						cout<<"Weight : "<<(*graph)[edge_descr]<<endl;
						cout<<"----------------------"<<endl;
						*/
			    	}
			    	++index;
			    }
			}
			Py_DECREF(keys[0]);
			Py_DECREF(keys[1]);
			Py_DECREF(values[0]);
			Py_DECREF(values[1]);
		}
		return graph;
	}
}