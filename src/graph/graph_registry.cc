/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_registry.h"
#ifdef DEBUG
#include <iostream>
#include "../utils/algorithm.h"
#endif /*DEBUG*/

using std::map;
using std::vector;
using std::string;

namespace path_finder
{

	GraphRegistry GraphRegistry::_instance = GraphRegistry();

	GraphRegistry& GraphRegistry::Instance(){
		return GraphRegistry::_instance;
	}

	void GraphRegistry::AddGraph(const string& id,
								map<string, vector<string>>& data_map,
								vector<string>& factory_data)
	{
		if(GraphRegistry::_instance._registry.count(id) == 0){
			GraphFactory factory = GraphFactory(factory_data);
			cout<<&factory<<endl;
			GraphPtr_IdMap g = factory.CreateGraph(data_map);
			GraphRegistry::_instance._registry.insert(
				std::pair<string, GraphPtr_IdMap>(id,g));
		}
	}

	GraphPtr_IdMap GraphRegistry::GetGraph(string& id){
		return GraphRegistry::_instance._registry[id];
	}

	GraphRegistry::GraphRegistry(){
		GraphRegistry::_instance._registry = map<string, GraphPtr_IdMap>();
	}

	#ifdef DEBUG
	void GraphRegistry::PrintGraph(GraphPtr_IdMap graph){
		/* Boost-property accessors */
		IndexMap node_index = boost::get(boost::vertex_index, *(graph.first));
		/* local vars */
		auto vertexes = boost::vertices(*(graph.first));
		auto ids_map = Algorithm::GetReversedMap<string, luint>(graph.second);
		std::cout<<"---PRINT GRAPH ---"<< std::endl;
		std::cout<<"VERTEX_ID (INDEX) : NEIGHBOR_ID (INDEX) = COST"<< std::endl;
		for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
			auto neighbors = boost::adjacent_vertices(*v_it, *(graph.first));
			int v_index = node_index[*v_it];
			for (auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
				int n_index = node_index[*n_it];
				std::cout << ids_map[v_index] << "\t (" << v_index <<")\t :\t "
						<< ids_map[n_index] << "\t ("<< n_index <<")\t = "
						<< (*(graph.first))[boost::edge(*v_it,*n_it,*(graph.first)).first]
					<< std::endl;
			}
		}
	}
	#endif /*DEBUG*/
}