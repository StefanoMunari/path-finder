/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "ai.h"
#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;
/*
* WARNING: Avoid using "static" prefix for methods in file definitions
* cause it enables internal linkage making the methods visibile only
* inside the definition file
*/

namespace path_finder
{

	AI* AI::_instance=nullptr;
	GraphRegistry AI::_registry=GraphRegistry();
	//PathFinder AI::_path_finder=PathFinder();

	AI* AI::Instance(){
		return AI::_instance;
	}

	AI* AI::Instance(vector<string> factory_data,
		map<string, vector<string>> data_map){
		if(_instance == nullptr){
			AI::_instance= new AI(factory_data, data_map);
		}
		return AI::_instance;
	}

	AI::AI(vector<string>& factory_data,
		map<string, vector<string>>& data_map){
		AI::_registry.SetFactory(factory_data);
		AI::_registry.AddGraph("static", data_map);
	}

	#ifdef DEBUG
	void AI::Print(){
		AI::_registry.PrintGraph(AI::_registry.GetGraph("static"));
	}
	#endif /*DEBUG*/
}