template <typename State>
std::list<State>*
PathFinderActivator<State>::Find(const State& source,
	const State& destination, GraphRegistry& registry){
	string graph_name = "staticfootway";
	UniformCostSearch<State> finder =
		UniformCostSearch<State>(registry.GetGraph(graph_name));
	//GreedySearch<State>(registry.GetGraph(graph_name));
	graph_name = "staticfootway";
	return finder.Search(registry.GetGraph(graph_name),
		Problem<State>(source, destination));
};

#ifdef DEBUG
template <typename State>
void
PathFinderActivator<State>::PrintIDList(Node<State>* last){
	std::cout<<"PrintIDList -Start-"<<std::endl;
	std::cout<<"(Path from the last node to the first one)"<<std::endl;
	Node<State>* iterator = last;
	while(iterator){
		std::cout<<"NODE : "<<iterator->state<<std::endl;
		iterator = iterator->parent;
	}
	std::cout<<"PrintIDList -End-"<<std::endl;
};
#endif /*DEBUG*/