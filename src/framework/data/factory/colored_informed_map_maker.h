/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef COLORED_INFORMED_MAP_MAKER_H
#define COLORED_INFORMED_MAP_MAKER_H

#include "../node_colored.h"
#include "../../../utils/boost_types.h"
#include <map>
#include <string>
#include <utility>// std::pair
#include <climits>// UINT_MAX

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredInformedMapMaker;

	/**
	 * @brief  Factory of map<key, <ColoredNode, cost>>.
	 *
	 * Creates a map of CONNECTED nodes. Each node is initialized with a
	 * WHITE color and each edge with UINT_MAX cost by default.
	 * Each node is a key of the map,
	 * each entry referenced by a key contains a list of edges represented as
	 * pairs of node * and cost.
	 *
	 * @param ids_map - a map<vertex_id, vertex_name>
	 * @param graph - the graph which contains the vertexes and the edges
	 *
	 * @return map<ColoredNode*, [<ColoredNode*, cost>]> - key is a pointer to
	 *			the current node while the tuple <ColoredNode *, cost>
	 *			contains info on the node and its cost
	 *
	 * @pre the graph has only NOT negative costs
	*/
	template <typename State>
	class ColoredInformedMapMaker {
	  public:
		std::map<NodeColored<State> *, list<pair<NodeColored<State> *, uint>>> *
		MakeInformedMap(std::map<int, std::string> *, Graph *);
	};

	// import template implementation
	#include "colored_search_map_maker.cpp"
}
#endif /*COLORED_INFORMED_MAP_MAKER_H*/