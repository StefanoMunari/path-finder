template<typename State>
Searchable<State>* SearchableFactory::MakeSearchable(SearchableType algorithm){
	switch(algorithm){
		case UNIFORM_COST:
			return new UniformCostSearch<State>();
		case GREEDY:
			return new GreedySearch<State>();
		default:
			throw
				std::invalid_argument(
					"SearchableFactory::Invalid algorithm identifier");
			break;
	}
}