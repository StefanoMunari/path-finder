namespace path_finder
{
	#ifndef DICTIONARY_FACTORY_H
	#define DICTIONARY_FACTORY_H

	class DictionaryFactory{
		public:
			DictionaryFactory(const string&);
			PyDictObject* CreateDictionary(map<string, vector<string>>&);
		private:
			FunctionFactory _function_factory;
	};

	#endif /*DICTIONARY_FACTORY_H*/
}