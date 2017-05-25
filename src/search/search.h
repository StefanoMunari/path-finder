#ifndef SEARCH_H
#define SEARCH_H

//#include <vector>
//#include "../framework/problem/action.h"
#include "../framework/problem/problem.h"

namespace path_finder
{
	class Search{
	  public:
	  	//std::vector<Action>*
	    virtual void Search(Problem*) =0;
	};
}
#endif /*SEARCH_H*/