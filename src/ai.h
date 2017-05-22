/**
 * @file
 * @brief  Interface of the path-finder system
 * @author <stefanomunari.sm@gmail.com>
 *
 * Singleton class which acts as a Facade for the undelying system
 */
#ifndef AI_H
#define AI_H

#include "graph_registry.h"
#include "graph_observer.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder
{

	class AI{
		public:
			AI() =delete;
			AI(AI const&) =delete;
			void operator=(AI const&) =delete;
			static AI* Instance();
			static AI* Instance(std::vector<std::string> factory_data,
				std::map<std::string, std::vector<std::string>> data_map,
				const std::string& subject_file,
				const std::string& subject_dir);
			#ifdef DEBUG
			static void Print();
			#endif /*DEBUG*/
		protected:
			AI(std::vector<std::string>&,
				std::map<std::string, std::vector<std::string>>&,
				const std::string& subject_file, const std::string& subject_dir);
			//List<ID> find_path();
		private:
			static AI* _instance;
			static GraphRegistry _registry;
			static GraphObserver _graph_observer;
			//static PathFinder _path_finder;
	};
}

#endif /*AI_H*/