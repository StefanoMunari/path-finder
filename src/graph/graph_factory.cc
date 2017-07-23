/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_factory.h"
#include "../io/json_reader.h"

using std::map;
using std::vector;
using std::string;

namespace path_finder
{

GraphPtr_IdMap
GraphFactory::CreateGraph(
	const std::string& topology_path,
	const std::string& costs_path,
	const std::string& extension)
	const noexcept
{
	map<string, vector<string>> topology_map = map<string, vector<string>>();
	map<string, vector<uint>> costs_map = map<string, vector<uint>>();

	JSON_Reader::Read(topology_path+extension, &topology_map);
	JSON_Reader::Read(costs_path+extension, &costs_map);
	GraphEncoder encoder = GraphEncoder();
	GraphPtr_IdMap graph = encoder.Encode(&topology_map, &costs_map);

	return graph;
}

}