/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_registry.h"
//#include "../utils/synch.h"
#include <algorithm>// std::mismatch
#include <mutex>  // std::unique_lock
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
		// check if GraphRegistry is not already initialized
		// for the requested id
		if(GraphRegistry::_instance._static_registry.count(id) == 0){
			// initialize private fields
			GraphRegistry::_instance._graph_names.insert(
				std::pair<string, string>(
					id,
					data_map["configuration_paths"][0]));
			GraphRegistry::_instance._graph_factory =
										new GraphFactory(factory_data);
			GraphRegistry::_instance._reader_function_name =
										data_map["function_names"][0];
			// extract the static graph
			GraphPtr_IdMap g0 =
				GraphRegistry::_instance._graph_factory->CreateGraph(data_map);
			// make a copy of the extracted graph
			GraphPtr_IdMap * g1 = new GraphPtr_IdMap();
			g1->first = new Graph(*(g0.first));
			g1->second = new IdVertexMap(*(g0.second));
			// C++ map does not insert the element if the element's key
			// already exists in the map
			GraphRegistry::_instance._static_registry.insert(
				std::pair<string, GraphPtr_IdMap>(id,g0));

			auto destructor = [](GraphPtr_IdMap* graph_pair){
					delete graph_pair->first;
					delete graph_pair->second;
				};
			// use the static_graph values (by copy) for the default
			// dynamic graph. It will be updated when new information will
			// be provided through the Observer. These values works for
			// the initial computations of the paths.
			auto shared_graph = shared_ptr<GraphPtr_IdMap>(g1,destructor);
			GraphRegistry::_instance._dynamic_registry.insert(
				std::pair<string, shared_ptr<GraphPtr_IdMap>>(
					id, shared_graph));
		}
	}

	GraphPtr_IdMap GraphRegistry::GetStaticGraph(string& id){
		return GraphRegistry::_instance._static_registry[id];
	}

	shared_ptr<GraphPtr_IdMap> GraphRegistry::GetDynamicGraph(string& id){
		return GraphRegistry::_instance._dynamic_registry[id];
	}

	void GraphRegistry::UpdateDynamicRegistry(
		const string& graph_name, const string& config_path){
		map<string, vector<string>> data_map = map<string, vector<string>>();
		vector<string> functions = vector<string>();
		vector<string> configs = vector<string>();
		// get the graph_name (file) from the id
		const string id = GraphRegistry::_instance.GetId(graph_name);
		functions.push_back("get_dictionary_from_file");
		functions.push_back("get_dictionary_from_file");
		configs.push_back(config_path+id+"_graph_5n.json");
		// config_path+id+"_graph_5n.json"
		configs.push_back(config_path+id+"_cost_5n.json");
		// config_path+id+"_cost_5n.json"
		// config_path+graph_name
		data_map.insert(
			std::pair<string, vector<string>>("function_names", functions));
		data_map.insert(
			std::pair<string, vector<string>>("configuration_paths", configs));
		// extract the dynamic graph
		GraphPtr_IdMap * g = new GraphPtr_IdMap();
		(*g) = GraphRegistry::_instance._graph_factory->CreateGraph(data_map);
		// update the registry
		GraphRegistry::_instance.SyncUpdate(id, g);
	}

// ================================PRIVATE======================================

	GraphRegistry::GraphRegistry(){
		GraphRegistry::_instance._static_registry =
			map<string, GraphPtr_IdMap>();
		GraphRegistry::_instance._dynamic_registry =
			map<string, shared_ptr<GraphPtr_IdMap>>();
	}

	GraphRegistry::GraphRegistry(const GraphRegistry& that){
		/* since it is static class this body is empty/not needed */
	}

	GraphRegistry& GraphRegistry::operator= (const GraphRegistry&){
		/* since it is static class this body is empty/not needed */
		return GraphRegistry::_instance;
	}

	GraphRegistry::~GraphRegistry() noexcept{
		delete GraphRegistry::_instance._graph_factory;
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

	const std::string GraphRegistry::GetId(const std::string& graph_name) const
	{
		for(const auto& element : GraphRegistry::_instance._static_registry)
		{
			auto matched =
				std::mismatch(element.first.begin(), element.first.end(),
					graph_name.begin());

			if(matched.first == element.first.end())
				return element.first;
			else
				throw std::invalid_argument("GraphRegistry::GetId - Wrong key (" + graph_name + ") the prefix of the dynamic configuration file differs from the static one.");
		}
		return "";
	}

	void GraphRegistry::SyncUpdate(const std::string& id, GraphPtr_IdMap * g){
		auto destructor = [](GraphPtr_IdMap* graph_pair){
				delete graph_pair->first;
				delete graph_pair->second;
			};
		auto shared_graph = shared_ptr<GraphPtr_IdMap>(g, destructor);
		std::unique_lock<std::shared_mutex> lock(
   											GraphRegistry::_instance._mutex);
		GraphRegistry::_instance._dynamic_registry.erase(id);
		GraphRegistry::_instance._dynamic_registry.insert(
			std::pair<string, shared_ptr<GraphPtr_IdMap>>(id, shared_graph));
		std::unique_lock<std::shared_mutex> unlock(
   											GraphRegistry::_instance._mutex);
		/*
		// Notify Main - now can exit correctly
   		std::unique_lock<std::mutex> termination_lock(termination);
	    termination_lock.unlock();
	    wait_for_termination.notify_one();
	    */
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
					<< (*(graph.first))[boost::edge(
										*v_it,*n_it,*(graph.first)).first]
					<< std::endl;
			}
		}
	}
	#endif /*DEBUG*/
}