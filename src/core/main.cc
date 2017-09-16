/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "ai.h"
#include "io/json_reader.h"
#include "search/utils/searchable_type.h"
#include "utils/constants.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <climits> // UINT_MAX
#include <iostream>
#include <stdlib.h> // getenv
#include <stdexcept>
#include <fstream> // std::ifstream

uint GetStepCost(std::map<std::string, std::vector<std::string>> * topology,
	std::map<std::string, std::vector<uint>> * costs,
	std::string prev, std::string node)
{
	int neigh_index = -1;
	uint step_cost = UINT_MAX;
	if(!prev.empty())
	{
		std::vector<std::string> neighs = (*topology)[prev];
		for(uint i=0; neigh_index == -1 && i < neighs.size(); ++i)
		{
			if(neighs[i] == node)
			{
				neigh_index = i;
				std::vector<uint> neigh_costs = (*costs)[prev];
				step_cost = neigh_costs[neigh_index];
			}
		}
	}
	return step_cost;
}

int main(int argc, char **argv){

	using path_finder::AI;
	using std::map;
	using std::vector;
	using std::string;
	using std::pair;

	if(argc != 3)
		throw std::invalid_argument("main - arguments not specified");

	const string source = argv[1];
	const string destination = argv[2];

	char * c_prefix = getenv(PROJECT_ROOT);

	if(c_prefix == nullptr)
		throw std::invalid_argument("main - environment var not specified");

	const string prefix = string(c_prefix);
	string data_path = "";
	string f_name_prefix = "";
	string f_extension = "";

	{
		std::ifstream configuration_stream =
			std::ifstream(prefix+CONFIGURATION_FILE, std::ifstream::in);
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
std::cout<<"qwe"<<std::endl;
	auto result1 =
		ai1.FindPath<string>(source, destination, path_finder::ASTAR);
std::cout<<"ASD"<<std::endl;
	std::map<std::string, std::vector<std::string>> * topology =
		new std::map<std::string, std::vector<std::string>>();
	std::map<std::string, std::vector<uint>> * costs =
		new std::map<std::string, std::vector<uint>>();

	path_finder::JSON_Reader::Read(
		prefix+data_path+f_name_prefix+"-topology"+f_extension,
		topology);

	path_finder::JSON_Reader::Read(
		prefix+data_path+f_name_prefix+"-costs"+f_extension,
		costs);

	std::cout<<"--------------SEARCH RESULTS--------------"<<std::endl;
	std::cout<<"==========UNIFORM COST========="<<std::endl;
	{
		std::string prev = "";
		uint total_cost = 0;
		if(result)
		{
			for(auto const& node : (*result))
			{
				uint step_cost = GetStepCost(topology, costs, prev, node);
				if(step_cost != UINT_MAX)
				{
					std::cout<< "cost => "<< step_cost <<std::endl;
					total_cost = total_cost+step_cost;
				}
				std::cout<< node <<std::endl;
				prev = node;
			}
		std::cout<< "TOTAL COST : "<< total_cost <<std::endl;
		}
	}

	std::cout<<"==========GREEDY========="<<std::endl;
	{
		std::string prev = "";
		uint total_cost = 0;
		if(result0)
		{
			for(auto const& node : (*result0)) {
				uint step_cost = GetStepCost(topology, costs, prev, node);
				if(step_cost != UINT_MAX)
				{
					std::cout<< "cost => "<< step_cost <<std::endl;
					total_cost = total_cost+step_cost;
				}
				std::cout<< node <<std::endl;
				prev = node;
			}
			std::cout<< "TOTAL COST : "<< total_cost <<std::endl;
		}
	}

	std::cout<<"==========ASTAR========="<<std::endl;
	{
		std::string prev = "";
		uint total_cost = 0;
		for(auto const& node : (*result1)) {
			uint step_cost = GetStepCost(topology, costs, prev, node);
			if(step_cost != UINT_MAX)
			{
				std::cout<< "cost => "<< step_cost <<std::endl;
				total_cost = total_cost+step_cost;
			}
			std::cout<< node <<std::endl;
			prev = node;
		}
		std::cout<< "TOTAL COST : "<< total_cost <<std::endl;
	}
	std::cout<<"------------------------------------------"<<std::endl;

	delete result;
	delete result0;
	delete result1;
	delete topology;
	delete costs;

	return 0;
}