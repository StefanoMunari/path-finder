/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <boost/foreach.hpp>
#include <map>
#include <utility>

namespace path_finder{

	class Algorithm {
		public:
			template<typename T0, typename T1>
			static std::map<T1, T0>
			GetReversedMap(std::map<T0, T1>* to_reverse);
	};

/***************************IMPLEMENTATION*************************************/

	template<typename T0, typename T1>
	std::map<T1, T0>
	Algorithm::GetReversedMap(std::map<T0, T1>* to_reverse){
		/* iterator for a std::map to reverse */
		std::pair<T0, T1> iterator;
		/* the resulting reversed std::map */
		std::map<T1, T0> reversed;
		BOOST_FOREACH(iterator, (*to_reverse)) {
		  reversed.insert(std::pair<T1, T0>(iterator.second, iterator.first));
		}
		return reversed;
	}

}
#endif /*ALGORITHM_H*/