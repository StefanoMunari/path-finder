#ifndef SEARCHABLE_H
#define SEARCHABLE_H

//#include <vector>
//#include "../framework/problem/action.h"
#include "../framework/problem/problem.h"
#include "../framework/data/node.h"
#include "../utils/boost_types.h"

namespace path_finder
{
	template <typename State> class Searchable;

	template <typename State>
	class Searchable{
	  public:
	  	//std::vector<Action>*
	    virtual Node<State>* Search(Graph*, const Problem<State>&) =0;
	};
}
#endif /*SEARCHABLE_H*/