namespace path_finder
{
	#ifndef GRAPH_ENCODER_H
	#define GRAPH_ENCODER_H

	class GraphEncoder{
		public:
			GraphEncoder(){};
			Graph* Encode(PyDictObject*, PyDictObject*);
	};

	#endif /*GRAPH_ENCODER_H*/
}