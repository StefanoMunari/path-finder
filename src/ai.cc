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

using std::map;
using std::vector;
using std::list;
using std::string;

namespace path_finder
{
	//GraphObserver AI::_graph_observer = GraphObserver();

	AI::AI(vector<string>& factory_data, map<string, vector<string>>& data_map,
		const string& category, const string& subject_dir)
	{
		this->_category = category;
		GraphRegistry::Instance().AddGraph(category, data_map, factory_data);
		//AI::_graph_observer.Observe(subject_dir);
	}

	#ifdef DEBUG
	void AI::Print(void){
		GraphRegistry::Instance().PrintGraph(
			GraphRegistry::Instance().GetGraph(_category));
	}
	#endif /*DEBUG*/
}