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
#include "framework/problem/explicit_test.h"
#include <string>
#include <functional>

namespace path_finder
{

class AI{
	public:
		AI() = delete;
		AI(const string&, const string&, const string&);
		~AI() noexcept {};
		template<typename State>
		std::list<State>* FindPath(
				const std::string& source,
				const std::string& destination,
				SearchableType algorithm)
				const noexcept;
	public:
		#ifdef DEBUG
		void Print(void) const noexcept;
		#endif /*DEBUG*/
	private:
		//	Identify the category of the graph requested by the client.
		//	The category corresponds to the name prefix of the
		//	infrastructure/topology graph file.
		//	e.g.
		//	a pedestrian will instantiate an AI with sidewalk category.
		//	a car will instantiate an AI with a street category, etc.
		std::string _category;
};
// import template implementation
#include "ai.cpp"

}
#endif /*AI_H*/