/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_factory.h"
#include <python2.7/Python.h>

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	GraphFactory::GraphFactory(std::vector<std::string>& factory_data){
		int argc = factory_data.size();
		char * argv[1];
		argv[0] = const_cast<char*>(factory_data[0].c_str());
		Py_SetProgramName(const_cast<char*>(factory_data[0].c_str()));
		Py_Initialize();
		PySys_SetArgv(argc,argv);
		_dictionary_factory = DictionaryFactory
			(factory_data[0].substr(0, factory_data[0].size()-3),
				factory_data[1]);
		_graph_encoder = GraphEncoder();
	}

	GraphFactory::GraphFactory(const GraphFactory& that){
		this->_dictionary_factory = that._dictionary_factory;
		this->_graph_encoder = that._graph_encoder;
	}

	GraphFactory& GraphFactory::operator=(const GraphFactory& that){
		this->_dictionary_factory = that._dictionary_factory;
		this->_graph_encoder = that._graph_encoder;
		return *this;
	}

	GraphPtr_IdMap
	GraphFactory::CreateGraph(map<string, vector<string>>& data_map){
		/*
		 0 : = graph_data
		 1 : = costs_data
		*/
		return _graph_encoder.Encode(
				_dictionary_factory.CreateDictionary(
					data_map["function_names"][0],
					data_map["configuration_paths"][0]),
				_dictionary_factory.CreateDictionary(
					data_map["function_names"][1],
					data_map["configuration_paths"][1]));

	}
}