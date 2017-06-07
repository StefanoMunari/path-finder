/**
 * @file
 * @brief  Interface of the path-finder system
 * @author <stefanomunari.sm@gmail.com>
 *
 * Singleton class which acts as a Facade for the path-finding system
 */
#ifndef AI_H
#define AI_H

#include "graph/graph_registry.h"
//#include "graph/graph_observer.h"
#include "sched/path_finder_activator.h"
#include <map>
#include <vector>
#include <list>
#include <string>

namespace path_finder
{

	class AI{
		public:
			AI() =delete;
			AI(std::vector<std::string>&,
				std::map<std::string, std::vector<std::string>>&,
				const std::string& subject_file,
				const std::string& subject_dir);
			template<typename State>
			std::list<State>* FindPath(const std::string&, const std::string&);
			#ifdef DEBUG
			static void Print(void);
			#endif /*DEBUG*/
		private:
			//static GraphObserver _graph_observer;
			std::string _subject;
			PathFinderActivator<std::string> _path_finder;
	};


	template<typename State>
	list<State>* AI::FindPath(const string& source, const string& destination){
		return _path_finder.Find(source,
								destination,
								GraphRegistry::Instance());
	}

}

#endif /*AI_H*/