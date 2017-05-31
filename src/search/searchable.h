#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include "../framework/problem/problem.h"
#include "../utils/boost_types.h"
#include <list>

namespace path_finder
{
	template <typename State> class Searchable;

	template <typename State>
	class Searchable{
		public:
			virtual std::list<State>*
			Search(GraphPtr_IdMap, const Problem<State>&) =0;
	};
}
#endif /*SEARCHABLE_H*/