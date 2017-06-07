/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef DICTIONARY_FACTORY_H
#define DICTIONARY_FACTORY_H

#include "function_factory.h"
#include <map>
#include <vector>
#include <string>
#include <python2.7/Python.h>

namespace path_finder
{
	class DictionaryFactory{
		public:
			DictionaryFactory() {};
			DictionaryFactory(const std::string&, const std::string&);
			DictionaryFactory(const DictionaryFactory&);
			DictionaryFactory& operator=(const DictionaryFactory&);
			~DictionaryFactory() noexcept {};
			PyDictObject* CreateDictionary(const std::string&,
				const std::string&);
		private:
			FunctionFactory _function_factory;
	};
}

#endif /*DICTIONARY_FACTORY_H*/