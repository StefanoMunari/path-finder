#include "graph_registry.h"

namespace path_finder
{
	GraphRegistry::GraphRegistry(){
		_registry=map<string, Graph>();
	}

	void GraphRegistry::SetFactory(vector<string>& factory_data){
		_graph_factory=GraphFactory(factory_data.size(), 
			(char**) &factory_data[0]);
	}

	void GraphRegistry::AddGraph(const string& id,  
		map<string, vector<string>>& data_map){

		_registry.insert(std::pair<string, Graph>(id, 
			_graph_factory.CreateGraph(data_map)));	
	}

	Graph* GraphRegistry::GetGraph(const string& id){
		return _registry[id];
	}
}