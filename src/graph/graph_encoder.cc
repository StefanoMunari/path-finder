/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_encoder.h"
#include "../utils/algorithm.h"
#include "../utils/types.h"
#include <boost/graph/adjacency_list.hpp>
#include <map>
#include <vector>
#include <stdexcept>
#include <string>
#include <utility>

using std::map;
using std::vector;
using std::string;

namespace path_finder
{

GraphPtr_IdMap
GraphEncoder::Encode(
	std::map<std::string, std::vector<std::string>> *
	graph_dictionary,
	std::map<std::string, std::vector<uint>> *
	costs_dictionary)
	const
{

	if(graph_dictionary == nullptr || costs_dictionary == nullptr)
		throw std::invalid_argument("encoder - NULL argument");

	Graph* graph = nullptr;
	IdVertexMap* converter = nullptr;
	/* set up graph */
	graph = new Graph();
	/* vars */
	converter = new IdVertexMap();
	vector<vector<string>> neighbors = vector<vector<string>>();
	IndexMap node_index = boost::get(boost::vertex_index, (*graph));

	for(const auto& pair : (*graph_dictionary))
	{
		VertexDescriptor vertex_descr;
		vertex_descr = boost::add_vertex(vertex_descr,(*graph));
		std::string vertex_id = pair.first;
		converter->insert(
			std::pair<std::string, VertexDescriptor>(
				vertex_id, vertex_descr));
		neighbors.push_back(vector<string>());
		vector<string> values = pair.second;
		for(const string& element : values)
			neighbors[node_index[vertex_descr]].push_back(element);
	}

	VertexIterator it, end;
	boost::tie(it, end) = boost::vertices(*graph);
	auto ids_map = Algorithm::GetReversedMap<string, luint>(converter);
	for(const auto& pair : (*costs_dictionary))
	{
	    if(it != end)
	    {
	    	int size=neighbors[node_index[*it]].size();
	    	for(int i =0; i < size; ++i){
				VertexDescriptor neighbor_descr;
				//VertexDescriptor source_descr;
	    		neighbor_descr =
	    			(*converter)[neighbors[node_index[*it]][i]];
				//source_descr = (*graph)[node_index[*it]];
	    		const Weight cost = (uint) pair.second[i];
				boost::add_edge(*it,
								neighbor_descr,
								cost, (*graph)).first;
	    	}
	    	++it;
	    }
	}

	return std::pair<Graph*, IdVertexMap*>(graph, converter);
}

}