#include "graph_factory.h"

namespace path_finder
{
	GraphFactory::GraphFactory(const int& argc, char** argv){
		Py_SetProgramName(argv[0]);
		Py_Initialize();
		PySys_SetArgv(argc, argv);
		_dictionary_factory=DictionaryFactory(string(argv[0]));
		_graph_encoder=GraphEncoder();
	}

	Graph* GraphFactory::CreateGraph(map<string, vector<string>>& data_map){
		/*
		 0 := graph_data
		 1 := costs_data
		*/
		return _graph_encoder.Encode(
				_dictionary_factory.CreateDictionary(data_map["function_names"][0],
					data_map["configuration_paths"][0]), 
				_dictionary_factory.CreateDictionary(data_map["function_names"][1], 
					data_map["configuration_paths"][1]));

	}
}