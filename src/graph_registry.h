namespace path_finder
{
	#ifndef GRAPH_REGISTRY_H
	#define GRAPH_REGISTRY_H

	class GraphRegistry{
		public:
			GraphRegistry();
			void SetFactory(vector<string>&);
			void AddGraph(const string&, map<string, vector<string>>&);
			Graph* GetGraph(const string&);
		private:
			map<string, Graph> _registry;
			GraphFactory _graph_factory;
	};

	#endif /*GRAPH_REGISTRY_H*/
}