/**
 * @file
 * @brief  Interface of the path-finder system
 * @author <stefanomunari.sm@gmail.com>
 *
 * Singleton class which acts as a Facade for the undelying system
 */
#ifndef AI_H
#define AI_H

#include "graph/graph_registry.h"
//#include "graph/graph_observer.h"
//#include "sched/path_finder_activator.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder
{

	class AI{
		public:
			AI()  =delete;
			AI(AI const&)  =delete;
			void operator= (AI const&)  =delete;
			static AI* Instance();
			static AI* Instance(std::vector<std::string> factory_data,
				std::map<std::string, std::vector<std::string>> data_map,
				const std::string& subject_file,
				const std::string& subject_dir);
			//List<ID>
			//void FindPath();
			#ifdef DEBUG
			static void Print(void);
			#endif /*DEBUG*/
		protected:
			AI(std::vector<std::string>&,
				std::map<std::string, std::vector<std::string>>&,
				const std::string& subject_file, const std::string& subject_dir);
		private:
			static AI* _instance;
			static GraphRegistry _registry;
			//static GraphObserver _graph_observer;
			static std::string _subject;
			//static PathFinderActivator<std::string> _path_finder;
	};
}

#endif /*AI_H*/