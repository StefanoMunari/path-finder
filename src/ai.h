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
			std::list<State>* FindPath(const std::string&, const std::string&,
										SearchableType algorithm);
			#ifdef DEBUG
			static void Print(void);
			#endif /*DEBUG*/
		private:
			//static GraphObserver _graph_observer;
			std::string _subject;
	};

	template<typename State>
	list<State>* AI::FindPath(const string& source,
							const string& destination,
							SearchableType algorithm)
	{
		auto _lambda_find =
			[&source, &destination](Searchable<State>* finder)
			{
				std::string graph_name = "staticfootway";
				auto static_graphptr_idmap =
					GraphRegistry::Instance().GetGraph(graph_name);
				auto dynamic_graphptr_idmap =
					GraphRegistry::Instance().GetGraph(graph_name);
				auto path = finder->Search(static_graphptr_idmap,
									dynamic_graphptr_idmap,
									Problem<State>(source, destination));
				//delete graphptr_idmap;
				//delete finder;
				return path;
			};
		return
			_lambda_find(SearchableFactory::MakeSearchable<State>(algorithm));
	}

}

#endif /*AI_H*/