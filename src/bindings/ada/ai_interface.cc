#include "../core/ai_interface.h"
#include "../core/ai.h"
#include "../core/search/utils/searchable_type.h"
#include "../core/utils/constants.h"
#include <list>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <stdexcept>

using path_finder::AI;
using std::map;
using std::vector;
using std::string;
using std::pair;

static
std::map<std::string, AI*>
FS_ai_map_ = std::map<std::string, AI*>();

static
std::map<std::string, std::list<std::string>*>
FS_path_map_ = std::map<std::string, std::list<std::string>*>();

static
const char * FS_root_path_ = getenv(PROJECT_ROOT);

const int Get_Path_Size(const char * pid_)
{
	const string pid = string(pid_);
	if(pid.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path_Size- invalid argument");
	return FS_path_map_[pid]->size();
}

const char ** Get_Path(const char * pid_)
{
	string pid = string(pid_);
	if(pid.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - invalid argument");
	if(FS_path_map_.count(pid) == 0)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - no path for the request id : "+pid);

	const char ** path =
		(const char **) malloc(
			FS_path_map_[pid]->size() * sizeof(const char *));
	int index = 0;

	for(auto&& element : (*FS_path_map_[pid]))
	{
		path[index] =
			(const char *) malloc(sizeof(char) * strlen(element.c_str()));
		path[index] = element.c_str();
		++index;
	}
	return path;
}

void Find(
	const char * pid_,
	const char * source_,
	const char * destination_,
	const int algorithm_)
{
	if(algorithm_ < 0 || algorithm_ > 2)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - invalid algorithm");

	const string pid = string(pid_);
	const string source = string(source_);
	const string destination = string(destination_);

	if(pid.empty() || source.empty() || destination.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - arguments not specified");

	list<string> * path =
		FS_ai_map_[pid]->FindPath<string>(source, destination, algorithm_);

	if(FS_path_map_.count(pid) == 0 && path == nullptr)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - path not found");

	if(!(path == nullptr))
		FS_path_map_.insert(pair<string, list<string>*>(pid, path));

	// otherwise FS_path_map_ already contains a valid path => OK
}

void Init(
	const char * pid_,
	const char * data_path_,
	const char * f_name_prefix_,
	const char * f_extension_)
{
	if(FS_root_path_ == NULL)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - environment variable unset");

	const string pid = string(pid_);
	const string data_path = string(data_path_);
	const string f_name_prefix = string(f_name_prefix_);
	const string f_extension = string(f_extension_);

	if(data_path.empty() || f_name_prefix.empty() || f_extension.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - arguments not specified");

	AI * ai = new AI(prefix+data_path, f_name_prefix, f_extension);
	FS_ai_map_.insert(pair<string, AI *>(pid, ai));
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
		free(FS_root_path_);
}