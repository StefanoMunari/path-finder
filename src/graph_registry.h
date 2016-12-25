#ifndef GRAPH_REGISTRY_H
#define GRAPH_REGISTRY_H

#include <map>
#include <vector>
#include <string>

namespace path_finder
{
	class GraphRegistry{
		public:
			GraphRegistry();
			void SetFactory(std::vector<std::string>&);
			void AddGraph(const std::string&, 
				std::map<string, std::vector<std::string>>&);
			Graph* GetGraph(const std::string&);
		private:
			std::map<std::string, Graph> _registry;
			GraphFactory _graph_factory;
	};
}

#endif /*GRAPH_REGISTRY_H*/