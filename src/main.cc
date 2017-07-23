/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "ai.h"
#include "search/utils/searchable_type.h"
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
	string data_path = "";
	string f_name_prefix = "";
	string f_extension = "";

	{
		std::ifstream configuration_stream =
			std::ifstream(prefix+"/etc/path_finder.conf", std::ifstream::in);
		string line;
		int vline_counter = 0;

		while(
			configuration_stream.good()
			&&
			std::getline(configuration_stream, line))
		{

	        if(line[0] != '#')// not a commented line
			{
				switch(vline_counter){
					case 0:
						data_path = line;
						break;
					case 1:
						f_name_prefix = line;
						break;
					case 2:
						f_extension = line;
						break;
					default:
						throw std::invalid_argument(
						"main - configuration file, bad formatting : "+line);
				}
				++vline_counter;
			}
		}

		if(!configuration_stream.eof())
			throw std::invalid_argument(
				"main - configuration stream error : "+line);
		if(data_path.empty() || f_name_prefix.empty() || f_extension.empty())
			throw std::invalid_argument(
				"main - empty arguments from configuration stream");
	}

	AI ai = AI(prefix+data_path, f_name_prefix, f_extension);
	AI ai0 = AI(prefix+data_path, f_name_prefix, f_extension);
	AI ai1 = AI(prefix+data_path, f_name_prefix, f_extension);

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
	for(auto const& node : (*result1)) {
	    std::cout<< node <<std::endl;
	}

	delete result;
	delete result0;
	delete result1;

	return 0;
}