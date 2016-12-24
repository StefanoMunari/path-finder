namespace path_finder
{
	#ifndef GRAPH_FACTORY_H
	#define GRAPH_FACTORY_H

	class GraphFactory{
		public:
			GraphFactory(const int&, char**);
			Graph* CreateGraph(map<string, vector<string>>&);
		private:
			DictionaryFactory _dictionary_factory;
			GraphEncoder _graph_encoder;
	};

	#endif /*GRAPH_FACTORY_H*/
}