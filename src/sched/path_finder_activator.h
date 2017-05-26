#ifndef PATH_FINDER_ACTIVATOR_H
#define PATH_FINDER_ACTIVATOR_H

#include "../search/uninformed/uniform_cost_search.h"
#include "../framework/data/node.h"
#include <string>
#include <iostream>

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
		private:
			void PrintIDList(Node<State>*);
	};

	template <typename State>
	void
	PathFinderActivator<State>::Find(const State& source,
		const State& destination, GraphRegistry& registry){
		string graph_name = "staticfootway";
		UniformCostSearch<State> finder(registry.GetGraph(graph_name));
		graph_name = "staticfootway";
		Node<State>* last = finder.Search(registry.GetGraph(graph_name), Problem<State>(source, destination));
		PrintIDList(last);
	};

	template <typename State>
	void
	PathFinderActivator<State>::PrintIDList(Node<State>* last){
		Node<State>* iterator = last;
		while(iterator){
			std::cout<<"NODE : "<<iterator->state<<std::endl;
			iterator = iterator->parent;
		}
	};
}
#endif /*PATH_FINDER_ACTIVATOR_H*/