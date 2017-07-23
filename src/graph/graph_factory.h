/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_FACTORY_H
#define GRAPH_FACTORY_H

#include "graph_encoder.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder{

class GraphFactory
{
	public:
		GraphFactory() noexcept {}
		GraphFactory(const GraphFactory&) noexcept {}
		GraphFactory& operator=(const GraphFactory&) noexcept { return *this; }
		~GraphFactory() noexcept {}
		GraphPtr_IdMap
		CreateGraph(const std::string&, const std::string&, const std::string&)
		const noexcept;
};

}

#endif /*GRAPH_FACTORY_H*/