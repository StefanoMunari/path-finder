#ifndef DICTIONARY_FACTORY_H
#define DICTIONARY_FACTORY_H

#include "function_factory.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder
{
	class DictionaryFactory{
		public:
			DictionaryFactory(const std::string&);
			PyDictObject* CreateDictionary(std::map<std::string, 
				std::vector<string>>&);
		private:
			FunctionFactory _function_factory;
	};
}

#endif /*DICTIONARY_FACTORY_H*/