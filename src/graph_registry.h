/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_REGISTRY_H
#define GRAPH_REGISTRY_H

#include "graph_factory.h"
#include "boost_types.h"
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
				std::map<std::string, std::vector<std::string>>&);
			Graph* GetGraph(const std::string&);
			#ifdef DEBUG
			void PrintGraph(Graph* graph);
			#endif /*DEBUG*/
		private:
			std::map<std::string, Graph*> _registry;
			GraphFactory _graph_factory;
	};
}

#endif /*GRAPH_REGISTRY_H*/