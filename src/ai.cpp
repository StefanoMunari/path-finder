template<typename State>
list<State>* AI::FindPath(const string& source,
						const string& destination,
						SearchableType algorithm)
{
	auto _find =
		[this, &source, &destination](Searchable<State>* finder)
		{
			auto static_graphptr_idmap =
				GraphRegistry::Instance().GetStaticGraph(this->_category);
			auto dynamic_graphptr_idmap =
				GraphRegistry::Instance().GetDynamicGraph(this->_category);
			auto path = finder->Search(static_graphptr_idmap,
								dynamic_graphptr_idmap,
								Problem<State>(source, destination));
			/* free the resources */
			/* NOTE: do not delete the graphs because they directly refers
				the registry graphs */
			delete finder;
			/* return the result */
			return path;
		};
	return
		_find(SearchableFactory::MakeSearchable<State>(algorithm));
}