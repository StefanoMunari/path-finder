/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
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
			GraphFactory() = delete;
			GraphFactory(std::vector<std::string>&);
			GraphFactory(const GraphFactory&);
			GraphFactory& operator=(const GraphFactory&);
			~GraphFactory() noexcept {};
			GraphPtr_IdMap
				CreateGraph(std::map<std::string, std::vector<std::string>>&);
		private:
			DictionaryFactory _dictionary_factory;
			GraphEncoder _graph_encoder;
	};
}

#endif /*GRAPH_FACTORY_H*/