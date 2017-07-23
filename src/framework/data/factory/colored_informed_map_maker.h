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
#include "../utils/node_costs.h"
#include "../../../utils/boost_types.h"
#include "../../../utils/types.h"
#include <map>
#include <utility>// std::pair
#include <climits>// UINT_MAX
#include <functional>// std::function

namespace path_finder
{

template <typename State> class ColoredInformedMapMaker;
/**
 * @brief  Factory of map<key, <ColoredNode, costs>>.
 *
 * Creates a map of nodes with the associated costs struct useful for
 * informed searches. All costs are set to UINT_MAX by default.
 *
 * @param search_map - the search_map used in uninformed searches.
 *
 * @return the informed_map which contains a struct for the costs related
 *			to informed searches.
*/
template <typename State>
class ColoredInformedMapMaker{
  public:

	std::map<State, std::pair<NodeColored<State> *,NodeCosts *>> *
	MakeMap(std::map<std::string, std::pair<NodeColored<State> *, uint>> *);

	std::function<
				void
				(std::map<State,
						std::pair<NodeColored<State> *,NodeCosts *>> *)
				>
	MakeMapDestructor(void);
};

// import template implementation
#include "colored_informed_map_maker.cpp"

}
#endif /*COLORED_INFORMED_MAP_MAKER_H*/