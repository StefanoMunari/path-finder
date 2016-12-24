#include "ai.h"

namespace path_finder
{
	AI AI::_ai=nullptr;
	GraphRegistry AI::_registry=GraphRegistry();
	//PathFinder AI::_path_finder=PathFinder();

	AI* AI::Instance(vector<string>& factory_data, 
		map<string, vector<string>>& data_map){
		if(_ai == nullptr){
			_ai= new AI(factory_data, data_map);
		}
		return _instance;
	}

	AI::AI(vector<string>& factory_data, 
		map<string, vector<string>>& data_map){
		_registry.SetFactory(factory_data);
		_registry.AddGraph("static", data_map);
	}
}