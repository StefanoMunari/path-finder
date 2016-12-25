#include "dictionary_factory.h"

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	DictionaryFactory::DictionaryFactory(const string& file_name){
		// remove the format '.py' from the file name
		_function_factory=FunctionFactory(PyImport_Import(
			PyString_FromString(
				(file_name.substr(0, file_name.size()-3)).c_str())));
	}

	PyDictObject* DictionaryFactory::CreateDictionary(const string& function_name,
		const string& configuration_path){
		return PyObject_CallObject(
					_function_factory.CreateFunction(_module, function_name), 
					_function_factory.CreateArgument(configuration_path));
	}
}