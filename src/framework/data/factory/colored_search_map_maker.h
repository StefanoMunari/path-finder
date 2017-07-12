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

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredSearchMapMaker;

	template <typename State>
	class ColoredSearchMapMaker {
	  public:
		std::map<std::string, std::pair<NodeColored<State> *, uint>> *
		MakeSearchMap(State, std::map<int, std::string> *, Graph *);
	};

	// import template implementation
	#include "colored_search_map_maker.cpp"
}
#endif /*COLORED_SEARCH_MAP_MAKER_H*/