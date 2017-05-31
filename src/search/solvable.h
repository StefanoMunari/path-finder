/**
 * @file
 * @brief A solver interface.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef SOLVABLE_H
#define SOLVABLE_H

#include "../framework/data/node.h"
#include <list>

namespace path_finder
{
	template <typename State> class Solvable;

	template <typename State>
	class Solvable{
		public:
			/**
			 * Computes the resulting path starting from the goal node
			 * @param last - the goal node
			 * @return the list of states which represents the resulting path
			 */
			virtual std::list<State>* Solve(Node<State>* last) =0;
	};
}
#endif /*SOLVABLE_H*/