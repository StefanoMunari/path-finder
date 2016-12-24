#include "graph_encoder.h"

namespace path_finder
{
	Graph* GraphEncoder::Encode(PyDictObject* graph_dictionary, 
		PyDictObject* costs_graph){

		Graph* graph=nullptr;

		if(PyDict_Check(graph_dictionary) && PyDict_Check(cost_dictionary)){
			graph=new Graph();
			PyObject *keys[2], *values[2];
			Py_ssize_t positions[2] = {0};

			while (PyDict_Next(graph_dictionary, &positions[0], &keys[0], 
				&values[0])
			 && PyDict_Next(cost_dictionary, &positions[1], &keys[1], 
			 	&values[1])) {
				int vertex=PyObject_AsFileDescriptor(keys[0]);
			    boost::add_vertex(vertex, graph);
			    if(PyList_Check(values[0]) && PyList_Check(values[1])){
			    	int size=PyList_Size(values[0]);
			    	for(int i=0; i < size; ++i){
			    		int neighbor=
			    			PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[0],i));
			    		int cost=
			    			PyObject_AsFileDescriptor(
			    				PyList_GetItem(values[1],i));
			    		boost::add_edge(vertex, neighbor, 
			    			EdgeWeigthProperty(cost), graph);
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