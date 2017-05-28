/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_encoder.h"
#include "../utils/algorithm.h"
#include <boost/graph/adjacency_list.hpp>
#include <map>
#include <vector>
#include <string>
#include <utility>
#ifdef DEBUG
#include <iostream>
#endif /*DEBUG*/
using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	GraphPtr_IdMap GraphEncoder::Encode(PyDictObject* graph_dictionary,
		PyDictObject* costs_dictionary){
		Graph* graph = nullptr;
		IdVertexMap* converter = nullptr;

		if(PyDict_Check(graph_dictionary) && PyDict_Check(costs_dictionary)){
			/* set up graph */
			graph = new Graph();
			/* vars */
			converter = new IdVertexMap();
			vector<vector<string>> neighbors = vector<vector<string>>();
			IndexMap node_index = boost::get(boost::vertex_index, (*graph));
			/* PyC objects */
			PyObject *keys[2], *values[2];
			Py_ssize_t positions[2] = {0};

			while(PyDict_Next((PyObject*) graph_dictionary,
				&positions[0], &keys[0], &values[0]))
			{
			  if(PyList_Check(values[0])){
					VertexDescriptor vertex_descr;
					vertex_descr = boost::add_vertex(vertex_descr,(*graph));
					//(*graph)[index] = index;
					std::string vertex_id = PyString_AsString(PyObject_Str(keys[0]));
					converter->insert(
						std::pair<std::string, VertexDescriptor>(
							vertex_id, vertex_descr));
					neighbors.push_back(vector<string>());
					int size = PyList_Size(values[0]);
					for(int i =0; i < size; ++i){
						std::string neighbor_id = PyString_AsString(PyObject_Str(
							PyList_GetItem(values[0],i)));
						neighbors[node_index[vertex_descr]].push_back(neighbor_id);
					}
				}
			}
			VertexIterator it, end;
			boost::tie(it, end) = boost::vertices(*graph);
			auto ids_map = Algorithm::GetReversedMap<string, luint>(converter);
			while(PyDict_Next((PyObject*) costs_dictionary, &positions[1],
			 	&keys[1], &values[1]))
			{
			    if(PyList_Check(values[1]) && it != end){
			    	int size=neighbors[node_index[*it]].size();
			    	for(int i =0; i < size; ++i){
						VertexDescriptor neighbor_descr;
						//VertexDescriptor source_descr;
			    		neighbor_descr = (*converter)[neighbors[node_index[*it]][i]];
						//source_descr = (*graph)[node_index[*it]];
			    		const Weight cost = ((unsigned int)
			    				PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[1],i)));
			    		#ifdef DEBUG
						EdgeDescriptor edge_descr =
						#endif /*DEBUG*/
						boost::add_edge(*it,
										neighbor_descr,
										cost, (*graph)).first;
						#ifdef DEBUG
						std::cout<<"Source : "<< ids_map[node_index[*it]]<<
						" = > Index Source: "<< node_index[*it] <<std::endl;
						std::cout<<"Neighbor : "<<neighbors[node_index[*it]][i]<<
						" = > Index Neighbor: "<< node_index[neighbor_descr] <<std::endl;
						std::cout<<"Weight : "<<(*graph)[edge_descr]<<std::endl;
						std::cout<<"----------------------"<<std::endl;
						#endif /*DEBUG*/
			    	}
			    	++it;
			    }
			}
			Py_DECREF(keys[0]);
			Py_DECREF(keys[1]);
			Py_DECREF(values[0]);
			Py_DECREF(values[1]);
		}
		return std::pair<Graph*, IdVertexMap*>(graph, converter);
	}
}