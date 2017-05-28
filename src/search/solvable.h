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
			virtual std::list<State>* Solve(Node<State>*) =0;
	};
}
#endif /*SOLVABLE_H*/