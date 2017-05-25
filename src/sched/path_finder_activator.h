#ifndef PATH_FINDER_ACTIVATOR_H
#define PATH_FINDER_ACTIVATOR_H

#include "../search/uninformed/uniform_cost_search.h"

namespace path_finder
{
	template <typename State> class PathFinderActivator;

	template <typename State>
	class PathFinderActivator{
	  public:
	    void PathFinderActivator() noexcept {};
		void Find(const State&, const State&, const GraphRegistry&);
	};

	template <typename State>
	void
	PathFinderActivator<State>::Find(const State& source,
		const State& destination, const GraphRegistry& registry){
		UniformCostSearch<State> finder(registry.GetGraph("staticfootway"));
		finder.Search(registry.GetGraph("dynamicfootway"), Problem(source, destination));
	};
}
#endif /*PATH_FINDER_ACTIVATOR_H*/