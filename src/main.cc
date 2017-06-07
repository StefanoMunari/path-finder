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
#include <list>
#include <string>
#include <utility>
#include <iostream>

int main(int argc, char **argv){

	using path_finder::AI;
	using std::map;
	using std::vector;
	using std::string;
	using std::pair;

	if(argc != 3)
		return 1;

	const string source=argv[1];
	const string destination=argv[2];

	vector<string> factory_data = vector<string>();
	vector<string> function_names = vector<string>();
	vector<string> configuration_paths = vector<string>();
	map<string, vector<string>> data_map = map<string, vector<string>>();

	factory_data.push_back("reader.py");
	factory_data.push_back("/home/m/Git/path-finder/src/io/");
	function_names.push_back("get_dictionary_from_file");
	function_names.push_back("get_dictionary_from_file");
	configuration_paths.push_back("/home/m/Git/path-finder/data/smallromania_graph_5n.json");
	configuration_paths.push_back("/home/m/Git/path-finder/data/smallromania_cost_5n.json");

	data_map.insert(
		pair<string, vector<string>>(
			"function_names", function_names));
	data_map.insert(
		pair<string, vector<string>>(
			"configuration_paths", configuration_paths));
	AI ai = AI(factory_data, data_map,"footway","/home/m/Git/path-finder/data");
	AI ai0 = AI(factory_data, data_map,"footway","/home/m/Git/path-finder/data");
	auto result = ai.FindPath<std::string>(source, destination);
	auto result0 = ai0.FindPath<std::string>(source, destination);
	std::cout<<"==========PRINT RESULT========="<<std::endl;
	for(auto const& node : (*result)) {
	    std::cout<< node <<std::endl;
	}
	for(auto const& node : (*result0)) {
	    std::cout<< node <<std::endl;
	}
	std::cout<<&ai<<std::endl;
	std::cout<<&ai0<<std::endl;
	return 0;
}