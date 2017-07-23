/**
 * @file
 * @brief Interface for the solver.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef SOLVABLE_H
#define SOLVABLE_H

#include "../framework/data/node.h"
#include <list>

namespace path_finder
{
	template <typename State> class Solvable;


	/**
	 * @brief Interface for the solver.
	*/
	template <typename State>
	class Solvable{
		public:
			/**
			 * Computes the resulting path starting from the goal node
			 * @param last - the goal node
			 * @return the list of states which represents the resulting path
			 */
			virtual
			std::list<State>* Solve(Node<State>* last)
			const noexcept =0;
	};
}
#endif /*SOLVABLE_H*/