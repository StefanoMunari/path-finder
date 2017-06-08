/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef SEARCHABLE_FACTORY_H
#define SEARCHABLE_FACTORY_H

#include "../searchable.h"
#include "../utils/searchable_type.h"
#include "../uninformed/greedy_search.h"
#include "../uninformed/uniform_cost_search.h"
#include <stdexcept>

namespace path_finder
{
	class SearchableFactory final{
		public:
			SearchableFactory() =delete;
			template<typename State>
			static Searchable<State>* MakeSearchable(SearchableType algorithm);
	};
	/* import template implementation */
	#include "searchable_factory.cpp"
}

#endif /*SEARCHABLE_FACTORY_H*/