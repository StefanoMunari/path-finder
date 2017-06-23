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
using std::shared_ptr;

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
		/*
			check if GraphRegistry is not already initialized
		*/
		if(GraphRegistry::_instance._static_registry.count(id) == 0){
			GraphFactory factory = GraphFactory(factory_data);
			GraphPtr_IdMap g0 = factory.CreateGraph(data_map);
			/* copy the extracted graph */
			GraphPtr_IdMap * g1 = new GraphPtr_IdMap();
			g1->first = new Graph(*(g0.first));
			g1->second = new IdVertexMap(*(g0.second));
			/*
				C++ map does not insert the element if the element's key
				already exists in the map
			*/
			GraphRegistry::_instance._static_registry.insert(
				std::pair<string, GraphPtr_IdMap>(id,g0));
			/*
				destructor used by shared_ptr<GraphPtr_IdMap>
			*/
			auto destructor = [](GraphPtr_IdMap* graph_pair){
					delete graph_pair->first;
					delete graph_pair->second;
				};
			/*
				use the static_graph values (by copy) for the default
				dynamic graph. It will be updated when new information will
				be provided through the Observer. These values works for
				the initial computations of the paths.
			*/
			GraphRegistry::_instance._dynamic_registry.insert(
				std::pair<string, shared_ptr<GraphPtr_IdMap>>(
					id,
					shared_ptr<GraphPtr_IdMap>(g1,destructor))
				);
		}
	}

	GraphPtr_IdMap GraphRegistry::GetStaticGraph(string& id){
		return GraphRegistry::_instance._static_registry[id];
	}

	shared_ptr<GraphPtr_IdMap> GraphRegistry::GetDynamicGraph(string& id){
		return GraphRegistry::_instance._dynamic_registry[id];
	}

	GraphRegistry::GraphRegistry(){
		GraphRegistry::_instance._static_registry =
			map<string, GraphPtr_IdMap>();
		GraphRegistry::_instance._static_registry =
			map<string, GraphPtr_IdMap>();
	}

	GraphRegistry::GraphRegistry(const GraphRegistry& that){
		/* since it is static class this body is empty/not needed */
	}

	GraphRegistry& GraphRegistry::operator= (const GraphRegistry&){
		/* since it is static class this body is empty/not needed */
		return GraphRegistry::_instance;
	}

	GraphRegistry::~GraphRegistry() noexcept{
		/* free the static registry */
		for(auto & element : GraphRegistry::_instance._static_registry){
			delete element.second.first;
			delete element.second.second;
		}
		/* free the dynamic registry */
		GraphRegistry::_instance._dynamic_registry.erase(
			GraphRegistry::_instance._dynamic_registry.begin(),
			GraphRegistry::_instance._dynamic_registry.end());
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