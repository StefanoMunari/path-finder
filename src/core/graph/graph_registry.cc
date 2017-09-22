/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_registry.h"
#include "../utils/synch.h"// G_mutex_graph
#include "../utils/types.h"// luint
#include <algorithm>// std::mismatch
#include <mutex>  // std::unique_lock
#include <shared_mutex>
#include <stdexcept>

#ifdef DEBUG
#include <iostream>
#include "../utils/algorithm.h"
#endif /*DEBUG*/

using std::map;
using std::vector;
using std::shared_ptr;
using std::string;

namespace path_finder
{
// Singleton
GraphRegistry GraphRegistry::_instance = GraphRegistry();

// G_ prefix for global variables
extern std::shared_mutex G_mutex_graph;

// FS_ prefix for file-scoped vars
static auto FS_destructor =
	[](GraphPtr_IdMap * graph_pair){
		delete graph_pair->first;
		delete graph_pair->second;
	};

GraphRegistry& GraphRegistry::Instance() noexcept
{
	return GraphRegistry::_instance;
}

void GraphRegistry::InsertGraph(
	const string& id, const string& file_path, const string& extension)
{
	// check if GraphRegistry is NOT already initialized for the requested id
	if(GraphRegistry::_instance._static_registry.count(id) == 0)
	{
		GraphFactory factory = GraphFactory();

		try
		{
		// extract the static graph
		GraphPtr_IdMap g0 = factory.CreateGraph(
			file_path+"-topology", file_path+"-costs", extension);

		// make a copy of the extracted graph
		GraphPtr_IdMap * g1 = new GraphPtr_IdMap();
		g1->first = new Graph(*(g0.first));
		g1->second = new IdVertexMap(*(g0.second));

		// C++ std::map does NOT insert the element if the element's key
		// already exists in the map
		GraphRegistry::_instance._static_registry.insert(
			std::pair<string, GraphPtr_IdMap>(id,g0));

		// use the static_graph values (by copy) for the default
		// dynamic graph. It will be updated when new information will
		// be provided through the Observer (@see UpdateDynamicRegistry).
		// The dynamic costs are acceptable because the ratio between the static
		// costs is preserved.
		auto shared_graph = shared_ptr<GraphPtr_IdMap>(g1, FS_destructor);

		GraphRegistry::_instance._dynamic_registry.insert(
			std::pair<string, shared_ptr<GraphPtr_IdMap>>(id, shared_graph));
		}
		catch (const std::exception& exc)
		{
			throw;
		}
	}
}

GraphPtr_IdMap GraphRegistry::GetStaticGraph(const string& id) noexcept
{
	return GraphRegistry::_instance._static_registry[id];
}

shared_ptr<GraphPtr_IdMap> GraphRegistry::GetDynamicGraph(
	const string& id) noexcept
{
	return GraphRegistry::_instance._dynamic_registry[id];
}

void GraphRegistry::UpdateDynamicRegistry(
	const string& f_path, const string& f_name)
{
	const int separator = f_name.find("-");
	const string id = f_name.substr(0, separator);
	const string extension = f_name.substr(f_name.find("."), f_name.size());
	string f_postfix = f_name.substr(separator, f_name.size());
	f_postfix = f_postfix.substr(0, f_postfix.find("."));

	GraphFactory factory = GraphFactory();
	GraphPtr_IdMap * g = new GraphPtr_IdMap();
	// extract the dynamic graph
	(*g) = factory.CreateGraph(
		f_path+id+"-topology", f_path+id+f_postfix, extension);
	// update the registry with the new computed graph
	GraphRegistry::_instance._SynchUpdate(id, g);
}

//================================PRIVATE=======================================

GraphRegistry::GraphRegistry() noexcept
{
	GraphRegistry::_instance._static_registry =
		map<string, GraphPtr_IdMap>();
	GraphRegistry::_instance._dynamic_registry =
		map<string, shared_ptr<GraphPtr_IdMap>>();
}

GraphRegistry::GraphRegistry(const GraphRegistry& that) noexcept
{
	/* since it is static class this body is empty/not needed */
}

GraphRegistry& GraphRegistry::operator= (const GraphRegistry&) noexcept
{
	/* since it is static class this body is empty/not needed */
	return GraphRegistry::_instance;
}

GraphRegistry::~GraphRegistry() noexcept
{
	// free the static registry
	for(auto & element : GraphRegistry::_instance._static_registry){
		delete element.second.first;
		delete element.second.second;
	}
	// free the dynamic registry
	GraphRegistry::_instance._dynamic_registry.erase(
		GraphRegistry::_instance._dynamic_registry.begin(),
		GraphRegistry::_instance._dynamic_registry.end());
}

void GraphRegistry::_SynchUpdate(const std::string& id, GraphPtr_IdMap * g)
{
	auto shared_graph = shared_ptr<GraphPtr_IdMap>(g, FS_destructor);
	{
	// <START> mutually exclusive region
	std::unique_lock<std::shared_mutex> g_lock(path_finder::G_mutex_graph);
	GraphRegistry::_instance._dynamic_registry.erase(id);
	GraphRegistry::_instance._dynamic_registry.insert(
		std::pair<string, shared_ptr<GraphPtr_IdMap>>(id, shared_graph));
	// <END> mutually exclusive region
	}
}

#ifdef DEBUG
void GraphRegistry::PrintGraph(GraphPtr_IdMap graph) noexcept
{
	// Boost-property accessors
	IndexMap node_index = boost::get(boost::vertex_index, *(graph.first));
	// local vars
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