/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_ENCODER_H
#define GRAPH_ENCODER_H

#include "../utils/boost_types.h"
#include <python2.7/Python.h>

namespace path_finder
{
	class GraphEncoder{
		public:
			GraphEncoder() {};
			GraphEncoder(const GraphEncoder& that) {};
			GraphEncoder& operator=(const GraphEncoder& that) { return *this; }
			~GraphEncoder() noexcept {};
			GraphPtr_IdMap Encode(PyDictObject*, PyDictObject*);
	};
}

#endif /*GRAPH_ENCODER_H*/