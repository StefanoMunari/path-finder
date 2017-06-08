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
#include "../utils/boost_types.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder
{
	class GraphRegistry{
		public:
			static GraphRegistry& Instance();
			static void AddGraph(const std::string&,
								std::map<std::string,std::vector<std::string>>&,
								std::vector<std::string>&);
			static GraphPtr_IdMap GetGraph(std::string&);
			#ifdef DEBUG
			void PrintGraph(GraphPtr_IdMap);
			#endif /*DEBUG*/
		protected:
			GraphRegistry();
			GraphRegistry(const GraphRegistry&);
			GraphRegistry& operator= (const GraphRegistry&);
			~GraphRegistry() noexcept;
		private:
			static GraphRegistry _instance;
			std::map<std::string, GraphPtr_IdMap> _registry;
	};
}

#endif /*GRAPH_REGISTRY_H*/