#ifndef GRAPH_ENCODER_H
#define GRAPH_ENCODER_H

#include <python2.7/Python.h>

namespace path_finder
{
	class GraphEncoder{
		public:
			GraphEncoder(){};
			Graph* Encode(PyDictObject*, PyDictObject*);
	};
}

#endif /*GRAPH_ENCODER_H*/