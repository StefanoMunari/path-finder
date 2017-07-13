/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "ai.h"
#include "search/utils/searchable_type.h"
//#include "utils/synch.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <iostream>
#include <stdlib.h> // getenv
#include <stdexcept>
#include <fstream> // std::ifstream

int main(int argc, char **argv){

	using path_finder::AI;
	//using path_finder::termination;
	//using path_finder::wait_for_termination;
	using std::map;
	using std::vector;
	using std::string;
	using std::pair;
	/*
	extern std::mutex termination;
	extern std::condition_variable wait_for_termination;
	*/

	if(argc != 3)
		throw std::invalid_argument("main - arguments not specified");

	const string source = argv[1];
	const string destination = argv[2];

	char * c_prefix = getenv("PATH_FINDER_ROOT");
	if(c_prefix == nullptr)
		throw std::invalid_argument("main - environment var not specified");

	const string prefix = string(c_prefix);
	string data_prefix = "";
	string key = "";
	vector<string> factory_data = vector<string>();
	vector<string> function_names = vector<string>();
	vector<string> configuration_paths = vector<string>();
	map<string, vector<string>> data_map = map<string, vector<string>>();

	{
		std::ifstream configuration_ptr =
			std::ifstream(prefix+"/etc/path_finder.conf", std::ifstream::in);
		string line;
		int vline_counter = 0;

		while (std::getline(configuration_ptr, line))
		{

	        if(line[0] != '#')// not a commented line
			{
				switch(vline_counter){
					case 0:
						factory_data.push_back(line);
						break;
					case 1:
						factory_data.push_back(prefix+line);
						break;
					case 2:
						function_names.push_back(line);
						function_names.push_back(line);
						break;
					case 3:
						data_prefix = line;
						break;
					case 4:
						configuration_paths.push_back(prefix+data_prefix+line);
						break;
					case 5:
						configuration_paths.push_back(prefix+data_prefix+line);
						break;
					case 6:
						key = line;
						break;
					default:
						throw std::invalid_argument(
						"main - configuration file, bad formatting : "+line);
				}
				++vline_counter;
			}
		}
	}

	data_map.insert(
		pair<string, vector<string>>(
			"function_names", function_names));
	data_map.insert(
		pair<string, vector<string>>(
			"configuration_paths", configuration_paths));

	AI ai = AI(factory_data, data_map, key, prefix+data_prefix);
	AI ai0 = AI(factory_data, data_map, key, prefix+data_prefix);
	AI ai1 = AI(factory_data, data_map, key, prefix+data_prefix);

	auto result =
		ai.FindPath<string>(source, destination, path_finder::UNIFORM_COST);
	auto result0 =
		ai0.FindPath<string>(source, destination, path_finder::GREEDY);
	auto result1 =
		ai1.FindPath<string>(source, destination, path_finder::ASTAR);

	std::cout<<"==========PRINT RESULT========="<<std::endl;
	std::cout<<"==========UNIFORM COST========="<<std::endl;
	for(auto const& node : (*result)) {
	    std::cout<< node <<std::endl;
	}
	std::cout<<"==========GREEDY========="<<std::endl;
	for(auto const& node : (*result0)) {
	    std::cout<< node <<std::endl;
	}
	std::cout<<"==========ASTAR========="<<std::endl;
	std::cout<<result1<<std::endl;
    // Necessary to wait for a signal from AI before releasing the static
    // memory. Otherwise Graph_Registry destructor is automatically invoked.
    // Main acts as the master thread
    // NOTE: this lock will not be used in the future when we will directly
    // use the AI as facade for the system. Only if we use the main process
    // written in C then this termination lock will be necessary.
/*
    {
        std::unique_lock<std::mutex> lock(termination);
        wait_for_termination.wait(lock, []{return 0;});
    }
*/
	return 0;
}