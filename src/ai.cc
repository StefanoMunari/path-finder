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
		const string& subject_file, const string& subject_dir)
	{
		this->_subject = subject_file;
		this->_path_finder = PathFinderActivator<string>();
		GraphRegistry::Instance().AddGraph("static"+subject_file,
			data_map, factory_data);
		//AI::_graph_observer.Observe(subject_dir);
	}

	#ifdef DEBUG
	void AI::Print(void){
		string name = "static"+_subject;
		GraphRegistry::Instance().PrintGraph(GraphRegistry::Instance().GetGraph(name));
	}
	#endif /*DEBUG*/
}