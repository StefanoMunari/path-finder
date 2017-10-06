#include "ai_interface.h"
#include "../../core/ai.h"
#include "../../core/search/utils/searchable_type.h"
#include "../../core/utils/constants.h"
#include <list>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <atomic>
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
//////////////////////////////
// FS : File Scoped variables
//////////////////////////////
static
std::map<std::string, AI*>
FS_ai_map_ = std::map<std::string, AI*>();

static
char const * FS_root_path_ = getenv("ADA_PROJECT_ROOT");

static
std::atomic<ushort>
FS_client_registry_index_ (0);

static
std::map<std::string, ushort>
FS_key_to_index_ = std::map<std::string, ushort>();


///////////////////////////////////////////
//	Key_To_Index[type_idX+agent_idA] => path0
//	Key_To_Index[type_idX+agent_idB] => path1
//	....
///////////////////////////////////////////
static
list<string> **
FS_paths_registry_ = EMPTY;
//////////////////////////////
// File Scoped functions
//////////////////////////////
static
const std::string Make_Key(const char * prefix, const char * postfix)
{
	return string(prefix)+string(postfix);
}
//////////////////////////////
// Public functions
//////////////////////////////
int Get_Path_Size(char * type_id_, char * agent_id_)
{
	const string key = Make_Key(type_id_, agent_id_);
try
{
	if(FS_key_to_index_.count(key) == 0)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path_Size- invalid argument");
	return (*(FS_paths_registry_[FS_key_to_index_[key]])).size();
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return -1;
}
}

char ** Get_Path(char * type_id_, char * agent_id_)
{
try
{
	const string type_id = string(type_id_);
	const string agent_id = string(agent_id_);
	const string key = Make_Key(type_id_, agent_id_);

	if(type_id.empty() || agent_id.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - invalid argument");
	if(FS_key_to_index_.count(key) == 0)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Get_Path - no path for the request type_id : "
			+type_id+" and requested agent_id : "+agent_id);

	char const ** path =
		(char const **) malloc(
			(*(FS_paths_registry_[FS_key_to_index_[key]])).size()
			* sizeof(char const *));

	int p_index = 0;
	for(auto&& element : (*(FS_paths_registry_[FS_key_to_index_[key]])))
	{
		path[p_index] =
			(char const *) malloc(sizeof(char) * strlen(element.c_str()));
		path[p_index] = element.c_str();
		++p_index;
	}

	return const_cast<char **>(path);
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return EMPTY;
}
}

bool Find(
	char * type_id_,
	char * agent_id_,
	char * source_,
	char * destination_,
	int algorithm_)
{
try
{
	// check if the algorithm has a valid identifier
	if(algorithm_ < 0 || algorithm_ > 2)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - invalid algorithm");

	const string type_id = string(type_id_);
	const string key = Make_Key(type_id_, agent_id_);
	const string source = string(source_);
	const string destination = string(destination_);
	SearchableType algorithm = SearchableType(algorithm_);

	// check if arguments are valid
	if(type_id.empty() || agent_id_ == EMPTY || source.empty()
		|| destination.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - arguments not specified");

	list<string> * path =
		FS_ai_map_[type_id]->FindPath<string>(source, destination, algorithm);

	// check if a path has been found
	if(path == EMPTY)
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Find - path not found");

	// remove the old path entry
	if(FS_paths_registry_[FS_key_to_index_[key]])
	{
		// remove the old path entry
		delete FS_paths_registry_[FS_key_to_index_[key]];
		// set the path entry to EMPTY
		FS_paths_registry_[FS_key_to_index_[key]] = EMPTY;
	}

	// path is already on the heap. Just copy the pointer to the heap and let
	// the path pointer/variable go out of scope.
	// NOTE: if this program point is reached then the path is not empty
	FS_paths_registry_[FS_key_to_index_[key]] = path;

	return true;
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return false;
}
}

bool Set_Clients_Limit(int clients_limit)
{
	if(FS_paths_registry_ == EMPTY)
	{
		FS_paths_registry_ = new list<string> *[clients_limit];
		FS_paths_registry_[clients_limit] = { EMPTY };
	}
	return true;
}

bool Init(
	char * type_id_,
	char * agent_id_,
	char * data_path_,
	char * f_name_prefix_,
	char * f_extension_)
{
try
{
	if(FS_root_path_ == EMPTY || FS_root_path_[0] == '\0')
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - environment variable unset");

	const string type_id = string(type_id_);
	const string key = Make_Key(type_id_, agent_id_);
	const string data_path = string(FS_root_path_) + string(data_path_);
	const string f_name_prefix = string(f_name_prefix_);
	const string f_extension = string(f_extension_);

	if(type_id.empty() || agent_id_ == EMPTY || data_path.empty()
		|| f_name_prefix.empty() || f_extension.empty())
		throw std::invalid_argument(
			"<Ada bindings>::AI_INTERFACE::Init - arguments not specified");

	AI * ai = new AI(data_path, f_name_prefix, f_extension);
	// one AI for each type of agent
	FS_ai_map_.insert(pair<string, AI *>(type_id, ai));
	// one path for each new agent
	// atomic op: returns the previous value and increment the FS_index
	const int client_index =
		FS_client_registry_index_.fetch_add(1, std::memory_order_relaxed);
	// map the key to the array indexes of the new client
	// @see FS_paths_registry_
	FS_key_to_index_.insert(pair<string, ushort>(key, client_index));
	// set the current path to EMPTY - not yet computed
	FS_paths_registry_[FS_key_to_index_[key]] = EMPTY;

	return true;
}
catch (const std::exception& exc)
{
	std::cerr << exc.what() << std::endl;
	return false;
}
}

bool Finalize(){
	// free the map of AIs
	for(auto & element : FS_ai_map_)
		delete element.second;
	// free the map of residual paths
	for(auto & element : FS_key_to_index_)
	{
		if(FS_paths_registry_[element.second])
			delete FS_paths_registry_[element.second];
	}
	delete FS_paths_registry_;
	// free the root_path variable
	if(FS_root_path_ != EMPTY)
		free(const_cast<char *>(FS_root_path_));
	// TODO: Finalize the Observer
	return true;
}