#ifndef GRAPH_FACTORY_H
#define GRAPH_FACTORY_H

#include "dictionary_factory.h"
#include "graph_encoder.h"
#include <map>
#include <vector>
#include <string>


namespace path_finder
{
	class GraphFactory{
		public:
			GraphFactory(const int&, char**);
			Graph* CreateGraph(map<string, vector<string>>&);
		private:
			DictionaryFactory _dictionary_factory;
			GraphEncoder _graph_encoder;
	};
}

#endif /*GRAPH_FACTORY_H*/