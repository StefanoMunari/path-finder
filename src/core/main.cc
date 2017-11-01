/**
 * @file
 * @brief  PoC main. Use it to prototype the algorithms.
 * @author <stefanomunari.sm@gmail.com>
 *
 *	Given a configuration file, it runs all the algoritms provided by the system
 * on the graph specified in the config file. It accepts as input the source and
 * the destination state to search for.
 * After the search phase, it prints the resulting paths with their
 * respective costs (also each step cost) to stdout.
 *
 */
#include "ai.h"
#include "graph/graph_observer.h"
#include "io/json_reader.h"
#include "search/utils/searchable_type.h"
#include "utils/constants.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <climits> // UINT_MAX
#include <stdlib.h> // getenv
#include <stdexcept>
#include <fstream> // std::ifstream
#include <iostream>

static
uint GetStepCost(
	std::map<std::string, std::vector<std::string>> * topology,
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

static
void Help(char **argv)
{
	std::cout<<"Usage:"<<std::endl;
	std::cout<<"\t " << argv[0] <<" <source> <destination> <config_file>"<<std::endl;
	std::cout<<"Example:"<<std::endl;
	std::cout<<"\t " << argv[0] <<" \"A\" \"C\" /etc/path_finder.conf"<<std::endl;
}

/*
 * Entrypoint - use it during the prototyping of the system.
 *
 *
 * @pre PATH_FINDER_ROOT environment variable is define.
 * @pre Program arguments are correctly provided.
 * @param argv contains 3 parameters: source, destination, config file path
 */
int main(int argc, char **argv)
{

	using path_finder::AI;
	using path_finder::GraphObserver;
	using std::map;
	using std::vector;
	using std::string;
	using std::pair;

try
{
	if(argc != 4)
	{
		Help(argv);
		throw std::invalid_argument("main - arguments not specified");
	}


	const string source = argv[1];
	const string destination = argv[2];
	const string conf_fpath = argv[3];

	char * c_prefix = getenv(PROJECT_ROOT);

	if(c_prefix == nullptr)
	{
		Help(argv);
		throw std::invalid_argument("main - environment var not specified");
	}

	const string prefix = string(c_prefix);
	string data_path = "";
	string f_name_prefix = "";
	string f_extension = "";

	{
		std::ifstream configuration_stream =
			std::ifstream(prefix+conf_fpath, std::ifstream::in);
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

	AI ai0 = AI(prefix+data_path, f_name_prefix, f_extension);
	AI ai1 = AI(prefix+data_path, f_name_prefix, f_extension);
	AI ai2 = AI(prefix+data_path, f_name_prefix, f_extension);

	auto result0 =
		ai0.FindPath<string>(source, destination, path_finder::UNIFORM_COST);

	auto result1 =
		ai1.FindPath<string>(source, destination, path_finder::GREEDY);

	auto result2 =
		ai2.FindPath<string>(source, destination, path_finder::ASTAR);

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
		if(result0)
		{
			for(auto const& node : (*result0))
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
		// check result0 - ignore if failed
		if(result1)
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
		else
			std::cout<< "SEARCH FAILED"<<std::endl;
	}

	std::cout<<"==========ASTAR========="<<std::endl;
	{
		std::string prev = "";
		uint total_cost = 0;

		for(auto const& node : (*result2)) {
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

	delete result0;
	delete result1;
	delete result2;
	delete topology;
	delete costs;

	ai0.Finalize();
	ai1.Finalize();
	ai2.Finalize();

	return 0;
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
}
}