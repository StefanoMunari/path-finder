#include "ai.h"

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	AI AI::_ai=nullptr;
	GraphRegistry AI::_registry=GraphRegistry();
	//PathFinder AI::_path_finder=PathFinder();

	static AI* AI::Instance(vector<string>& factory_data, 
		map<string, vector<string>>& data_map){
		if(_instance == nullptr){
			_instance= new AI::AI(factory_data, data_map);
		}
		return _instance;
	}

	static AI::AI(vector<string>& factory_data, 
		map<string, vector<string>>& data_map){
		_registry.SetFactory(factory_data);
		_registry.AddGraph("static", data_map);
	}
}