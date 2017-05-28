#ifndef PATH_FINDER_ACTIVATOR_H
#define PATH_FINDER_ACTIVATOR_H

#include "../search/uninformed/greedy_search.h"
#include "../search/uninformed/uniform_cost_search.h"
#include "../framework/data/node.h"
#include <string>
#include <list>
#ifdef DEBUG
#include <iostream>
#endif /*DEBUG*/

using std::string;
/* TODO: refactoring to scheduler */
namespace path_finder
{
	template <typename State> class PathFinderActivator;

	template <typename State>
	class PathFinderActivator{
		public:
			PathFinderActivator() noexcept {};
			~PathFinderActivator() noexcept {};
			std::list<State>*
			Find(const State&, const State&, GraphRegistry&);
		#ifdef DEBUG
		private:
			void PrintIDList(Node<State>*);
		#endif /*DEBUG*/
	};
	/* import template implementation */
	#include "path_finder_activator.cpp"
}
#endif /*PATH_FINDER_ACTIVATOR_H*/