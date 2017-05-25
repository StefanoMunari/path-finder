/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_registry.h"
#include <iostream>

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	GraphRegistry::GraphRegistry(){
		_registry=map<string, Graph*>();
	}

	void GraphRegistry::SetFactory(vector<string>& factory_data){
		_graph_factory=GraphFactory(factory_data);
	}

	void GraphRegistry::AddGraph(const string& id,
		map<string, vector<string>>& data_map){
		Graph* g = _graph_factory.CreateGraph(data_map);
		_registry.insert(std::pair<string, Graph*>(id,g));
	}

	Graph* GraphRegistry::GetGraph(const string& id){
		return _registry[id];
	}

	#ifdef DEBUG
	void GraphRegistry::PrintGraph(Graph* graph){
		/* Boost-property accessors */
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*graph));
		boost::property_map<Graph, boost::edge_weight_t>::type
			edge_cost = boost::get(boost::edge_weight, (*graph));
		/* local vars */
		auto vertexes= boost::vertices((*graph));

		std::cout<<"---PRINT GRAPH ---"<< std::endl;
		std::cout<<"VERTEX : NEIGHBOR = COST"<< std::endl;
		for(auto v_it= vertexes.first; v_it != vertexes.second; ++v_it){
		   auto neighbors= boost::adjacent_vertices(*v_it, (*graph));
		   for (auto n_it = neighbors.first; n_it != neighbors.second; ++n_it)
		       std::cout << node_id[*v_it] <<" : "
		       			 << node_id[*n_it] <<" = "
		       			 << edge_cost[boost::edge(*v_it,*n_it,(*graph)).first]
		      	<< std::endl;
	   }
	}
	#endif /*DEBUG*/
}