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
#include "../utils/constants.h"
#include <map>
#include <memory>// std::shared_ptr
#include <shared_mutex>
#include <vector>
#include <string>

namespace path_finder
{
	class GraphRegistry final {
		public:
			static GraphRegistry& Instance();
			static void AddGraph(const std::string&,
								std::map<std::string,std::vector<std::string>>&,
								std::vector<std::string>&);
			static GraphPtr_IdMap
				GetStaticGraph(std::string&);
			static std::shared_ptr<GraphPtr_IdMap>
				GetDynamicGraph(std::string&);
			static void
				UpdateDynamicRegistry(const std::string&, const std::string&);
			#ifdef DEBUG
			void PrintGraph(GraphPtr_IdMap);
			#endif /*DEBUG*/
		private:
			GraphRegistry();
			GraphRegistry(const GraphRegistry&);
			GraphRegistry& operator= (const GraphRegistry&);
			~GraphRegistry() noexcept;
			const std::string GetId(const std::string&) const;
			void SyncUpdate(const std::string&, GraphPtr_IdMap *);
			static GraphRegistry
				_instance;
			std::shared_mutex
				_mutex;
			GraphFactory *
				_graph_factory;
			std::string
				_reader_function_name = PYTHON_FUNCTION_NAME;
			std::map<std::string, GraphPtr_IdMap>
				_static_registry;
			std::map<std::string, std::shared_ptr<GraphPtr_IdMap>>
				_dynamic_registry;
			std::map<std::string, std::string>
				_graph_names;
	};
}

#endif /*GRAPH_REGISTRY_H*/