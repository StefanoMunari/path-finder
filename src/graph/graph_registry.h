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
#include <string>
#include <vector>

namespace path_finder{

class GraphRegistry final
{
	public:
		static
		GraphRegistry& Instance() noexcept;
		static
		void InsertGraph(
			const std::string&, const std::string&, const std::string&)
			noexcept;
		static
		GraphPtr_IdMap GetStaticGraph(std::string&) noexcept;
		static
		std::shared_ptr<GraphPtr_IdMap> GetDynamicGraph(std::string&) noexcept;
		static
		void UpdateDynamicRegistry(const std::string&, const std::string&);
	public:
		#ifdef DEBUG
		static
		void PrintGraph(GraphPtr_IdMap) noexcept;
		#endif /*DEBUG*/
	private:
		GraphRegistry() noexcept;
		GraphRegistry(const GraphRegistry&) noexcept;
		GraphRegistry& operator= (const GraphRegistry&) noexcept;
		~GraphRegistry() noexcept;
		void _SynchUpdate(const std::string&, GraphPtr_IdMap *);
	private:
		static
		GraphRegistry
			_instance;
		std::map<std::string, GraphPtr_IdMap>
			_static_registry;
		std::map<std::string, std::shared_ptr<GraphPtr_IdMap>>
			_dynamic_registry;
};

}
#endif /*GRAPH_REGISTRY_H*/