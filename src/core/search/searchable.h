/**
 * @file
 * @brief Interface for the search algorithms.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include "../utils/boost_types.h"
#include "../framework/problem/problem.h"
#include <memory>// std::shared_ptr
#include <list>

namespace path_finder
{
	template <typename State> class Searchable;

	/**
	 * @brief Interface for the search algorithms.
	 * @see boost_types.h
	 * @see problem.h
	*/
	template <typename State>
	class Searchable{
		public:
			Searchable() noexcept {};
			virtual ~Searchable() noexcept {};
			/**
			 * Search for a path from source to destination
			 * @param static_graph_ - a pair which contains info about the
			 * static graph (topology + static costs)
			 * @param dynamic_graph_ - a pointer to a pair which contains info
			 * about the current (dynamic) cost graph
			 * @param problem - an instance of a problem which contains info
			 *	about source and destination
			 * @return the list of states which represents the resulting path
			 */
			virtual std::list<State>*
			Search(GraphPtr_IdMap static_graph_,
					std::shared_ptr<GraphPtr_IdMap>
					dynamic_graph_,
					const Problem<State>& problem) =0;
	};
}
#endif /*SEARCHABLE_H*/