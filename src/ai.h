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
#include "search/factory/searchable_factory.h"
#include "search/utils/searchable_type.h"
#include "framework/problem/problem.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <functional>

namespace path_finder
{

	class AI{
		public:
			AI() =delete;
			AI(std::vector<std::string>&,
				std::map<std::string, std::vector<std::string>>&,
				const std::string& subject_file,
				const std::string& subject_dir);
			~AI() noexcept {};
			template<typename State>
			std::list<State>* FindPath(const std::string& source,
										const std::string& destination,
										SearchableType algorithm);
			#ifdef DEBUG
			static void Print(void);
			#endif /*DEBUG*/
		private:
			//	Identify the category of the graph requested by the client.
			//	The category corresponds to the name prefix of the
			//	infrastructure graph file.
			//	e.g.
			//	a pedestrian will instantiated an AI with sidewalk category
			//	a car will instantiate an AI with a street category, etc.
			std::string _category;
	};

	// import template implementation
	#include "ai.cpp"
}

#endif /*AI_H*/