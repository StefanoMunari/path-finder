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

		if(PyDict_Check(graph_dictionary) && PyDict_Check(costs_dictionary)){
			graph=new Graph();
			PyObject *keys[2], *values[2];
			Py_ssize_t positions[2] = {0};
			while
			(PyDict_Next((PyObject*) graph_dictionary,
				&positions[0], &keys[0], &values[0])
			 &&
			 PyDict_Next((PyObject*) costs_dictionary, &positions[1],
			 	&keys[1], &values[1]))
			{
				int vertex=PyObject_AsFileDescriptor(keys[0]);
				const VertexIndexProperty vertex_property=
					VertexIndexProperty (vertex);
			    boost::add_vertex(vertex_property, (*graph));
			    if(PyList_Check(values[0]) && PyList_Check(values[1])){
			    	int size=PyList_Size(values[0]);
			    	for(int i=0; i < size; ++i){
			    		int neighbor=
			    			PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[0],i));
			    		int cost=
			    			PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[1],i));
			    		const EdgeWeigthProperty cost_property=
			    			EdgeWeigthProperty(cost);
			    		boost::add_edge(
			    			VertexDescriptor (vertex),
			    			VertexDescriptor (neighbor),
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