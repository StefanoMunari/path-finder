#include "ai_interface.h"
#include "../../core/ai.h"
#include "../../core/search/utils/searchable_type.h"
#include "../../core/utils/constants.h"
#include <list>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

using path_finder::AI;
using path_finder::SearchableType;
using std::list;
using std::map;
using std::pair;
using std::string;
using std::vector;

static
std::map<std::string, AI*>
FS_ai_map_ = std::map<std::string, AI*>();

static
std::map<std::string, std::list<std::string>*>
FS_path_map_ = std::map<std::string, std::list<std::string>*>();

static
char const * FS_root_path_ = getenv("ADA_PROJECT_ROOT");

int Get_Path_Size(char * pid_)
{
	const string pid = string(pid_);
try
{
	if(pid.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path_Size- invalid argument");
	return FS_path_map_[pid]->size();
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return -1;
}
}

char ** Get_Path(char * pid_)
{
try
{
	string pid = string(pid_);
	if(pid.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - invalid argument");
	if(FS_path_map_.count(pid) == 0)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - no path for the request id : "+pid);

	char const ** path =
		(char const **) malloc(
			FS_path_map_[pid]->size() * sizeof(char const *));
	int index = 0;

	for(auto&& element : (*FS_path_map_[pid]))
	{
		path[index] =
			(char const *) malloc(sizeof(char) * strlen(element.c_str()));
		path[index] = element.c_str();
		++index;
	}
	return const_cast<char **>(path);
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return EMPTY;
}
}

void Find(
	char * pid_,
	char * source_,
	char * destination_,
	int algorithm_)
{
try
{
	if(algorithm_ < 0 || algorithm_ > 2)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - invalid algorithm");

	const string pid = string(pid_);
	const string source = string(source_);
	const string destination = string(destination_);
	SearchableType algorithm = SearchableType(algorithm_);

	if(pid.empty() || source.empty() || destination.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - arguments not specified");

	list<string> * path =
		FS_ai_map_[pid]->FindPath<string>(source, destination, algorithm);

	if(FS_path_map_.count(pid) == 0 && path == nullptr)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - path not found");

	if(!(path == nullptr))
		FS_path_map_.insert(pair<string, list<string>*>(pid, path));

	// otherwise FS_path_map_ already contains a valid path => OK
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
}
}

void Init(
	char * pid_,
	char * data_path_,
	char * f_name_prefix_,
	char * f_extension_)
{
try
{
	if(FS_root_path_ == NULL || FS_root_path_[0] == '\0')
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - environment variable unset");

	const string pid = string(pid_);
	const string data_path = string(FS_root_path_) + string(data_path_);
	const string f_name_prefix = string(f_name_prefix_);
	const string f_extension = string(f_extension_);

	if(data_path.empty() || f_name_prefix.empty() || f_extension.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - arguments not specified");

	AI * ai = new AI(data_path, f_name_prefix, f_extension);
	FS_ai_map_.insert(pair<string, AI *>(pid, ai));
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
}
}

void Finalize(){
	/* free the map of AIs */
	for(auto & element : FS_ai_map_)
		delete element.second;
	/* free the map of paths */
	for(auto & element : FS_path_map_)
		delete element.second;
	/* free the root_path variable */
	if(FS_root_path_ != NULL)
		free(const_cast<char *>(FS_root_path_));
}