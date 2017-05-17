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
#include <utility>
#include <iostream>

int main(int argc, char **argv){

	using path_finder::AI;
	using std::map;
	using std::vector;
	using std::string;
	using std::pair;

	vector<string> factory_data= vector<string>();
	vector<string> function_names= vector<string>();
	vector<string> configuration_paths= vector<string>();
	map<string, vector<string>> data_map= map<string, vector<string>>();

	factory_data.push_back("reader.py");
	factory_data.push_back("/home/m/Git/path-finder/src/");
	function_names.push_back("get_dictionary_from_file");
	function_names.push_back("get_dictionary_from_file");
	configuration_paths.push_back("/home/m/Git/path-finder/data/graph_10n.json");
	configuration_paths.push_back("/home/m/Git/path-finder/data/cost_10n.json");

	data_map.insert(
		pair<string, vector<string>>(
			"function_names", function_names));
	data_map.insert(
		pair<string, vector<string>>(
			"configuration_paths", configuration_paths));
	AI* ai= AI::Instance(factory_data, data_map);
	#ifdef DEBUG
	AI::Print();
	#endif /*DEBUG*/
	return 0;
}