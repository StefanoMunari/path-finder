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
	/* import template implementation */
	#include "algorithm.cpp"
}
#endif /*ALGORITHM_H*/