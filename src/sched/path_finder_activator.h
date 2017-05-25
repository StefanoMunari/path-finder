#ifndef PATH_FINDER_ACTIVATOR_H
#define PATH_FINDER_ACTIVATOR_H

#include "../search/uninformed/uniform_cost_search.h"
#include <string>

using std::string;

namespace path_finder
{
	template <typename State> class PathFinderActivator;

	template <typename State>
	class PathFinderActivator{
	  public:
	    PathFinderActivator() noexcept {};
	    ~PathFinderActivator() noexcept {};
		void Find(const State&, const State&, GraphRegistry&);
	};

	template <typename State>
	void
	PathFinderActivator<State>::Find(const State& source,
		const State& destination, GraphRegistry& registry){
		string graph_name="staticfootway";
		UniformCostSearch<State> finder(registry.GetGraph(graph_name));
		graph_name="dynamicfootway";
		finder.Search(registry.GetGraph(graph_name), Problem<State>(source, destination));
	};
}
#endif /*PATH_FINDER_ACTIVATOR_H*/