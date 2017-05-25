/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_encoder.h"
#include <boost/graph/adjacency_list.hpp>

namespace path_finder
{
	Graph* GraphEncoder::Encode(PyDictObject* graph_dictionary,
		PyDictObject* costs_dictionary){
		Graph* graph=nullptr;
		int index2=0;

		if(PyDict_Check(graph_dictionary) && PyDict_Check(costs_dictionary)){
			/* set up graph */
			graph=new Graph();
			/* Boost-property accessors */
			boost::property_map<Graph, boost::vertex_name_t>::type
				node_id = boost::get(boost::vertex_name, (*graph));
			boost::property_map<Graph, boost::vertex_index2_t>::type
				node_index2 = boost::get(boost::vertex_index2, (*graph));
			/* PyC objects */
			PyObject *keys[2], *values[2];
			Py_ssize_t positions[2] = {0};

			while
			(PyDict_Next((PyObject*) graph_dictionary,
				&positions[0], &keys[0], &values[0])
			 &&
			 PyDict_Next((PyObject*) costs_dictionary, &positions[1],
			 	&keys[1], &values[1]))
			{
				VertexDescriptor vertex_descr;
			    vertex_descr= boost::add_vertex((*graph));
				std::string vertex_id=PyString_AsString(PyObject_Str(keys[0]));
				node_id[vertex_descr]=vertex_id;
				node_index2[vertex_descr]=index2;
				++index2;
			    if(PyList_Check(values[0]) && PyList_Check(values[1])){
			    	int size=PyList_Size(values[0]);
			    	for(int i=0; i < size; ++i){
			    		std::string neighbor_id=PyString_AsString(PyObject_Str(
			    			PyList_GetItem(values[0],i)));
						VertexDescriptor neighbor_descr;
			   		 	neighbor_descr=boost::add_vertex((*graph));
						node_id[neighbor_descr]=neighbor_id;
						node_index2[neighbor_descr]=index2;
						++index2;
						PyList_GetItem(values[1],i);
			    		int cost=
			    			PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[1],i));
			    		const EdgeWeigthProperty cost_property=
			    			EdgeWeigthProperty((unsigned int) cost);
			    		boost::add_edge(vertex_descr, neighbor_descr,
			    			cost_property, (*graph));
			    	}
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