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