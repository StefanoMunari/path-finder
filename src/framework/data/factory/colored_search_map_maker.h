/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef COLORED_SEARCH_MAP_MAKER_H
#define COLORED_SEARCH_MAP_MAKER_H

#include "../node_colored.h"
#include "../../../utils/boost_types.h"
#include <map>
#include <string>
#include <utility>// std::pair
#include <climits>// UINT_MAX
#include <functional>// std::function

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredSearchMapMaker;
	/**
	 * @brief  Factory of map<key, <ColoredNode, cost>>.
	 *
	 * Creates a map of NOT connected nodes. Each node is initialized with a
	 * WHITE color and UINT_MAX cost by default, except the source node which
	 * is BLACK and has 0 as its initial cost.
	 *
	 * @param source - the source node
	 * @param ids_map - a map<vertex_id, vertex_name>
	 * @param graph - the graph which contains the vertexes and the edges
	 *
	 * @return map<key, <ColoredNode, cost>> - key are the vertex_names while
	 *			the tuple <ColoredNode, cost> contains info on the node and its
	 *			cost
	 *
	 * @pre the graph has only NOT negative costs
	*/
	template <typename State>
	class ColoredSearchMapMaker {
	  public:
		std::map<std::string, std::pair<NodeColored<State>*, uint>> *
		MakeMap(std::map<int, std::string> *, Graph *);
		std::function<
					void
					(std::map<std::string,
							std::pair<NodeColored<State>*, uint>> *)
					>
		MakeMapDestructor(void);
	};

	// import template implementation
	#include "colored_search_map_maker.cpp"
}
#endif /*COLORED_SEARCH_MAP_MAKER_H*/