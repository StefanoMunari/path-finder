#ifndef SEARCHABLE_H
#define SEARCHABLE_H

//#include <vector>
//#include "../framework/problem/action.h"
#include "../framework/problem/problem.h"

namespace path_finder
{
	template <typename State> class Searchable;

	template <typename State>
	class Searchable{
	  public:
	  	//std::vector<Action>*
	    virtual void Search(Problem<State>*) =0;
	};
}
#endif /*SEARCHABLE_H*/