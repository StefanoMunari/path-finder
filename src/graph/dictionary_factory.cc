/*
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "dictionary_factory.h"
#include <python2.7/Python.h>

using std::map;
using std::vector;
using std::string;

namespace path_finder
{
	DictionaryFactory::DictionaryFactory(const string& file_name,
		const std::string& directory){
		// add target directory to the current syspath env variable
		PyObject* sysPath = PySys_GetObject((char*)"path");
		PyList_Append(sysPath, PyString_FromString(directory.c_str()));
		// retrieve the target module
		PyObject * module = PyImport_Import(PyString_FromString(file_name.c_str()));
		// get the corresponding factory
		_function_factory = FunctionFactory(module);
	}

	DictionaryFactory::DictionaryFactory(const DictionaryFactory& that){
		this->_function_factory = that._function_factory;
	}

	DictionaryFactory& DictionaryFactory::operator=(
		const DictionaryFactory& that)
	{
		this->_function_factory = that._function_factory;
		return *this;
	}

	PyDictObject* DictionaryFactory::CreateDictionary
	(const string& function_name, const string& configuration_path){
		return (PyDictObject*) PyObject_CallObject(
						_function_factory.CreateFunction(function_name),
						_function_factory.CreateArgument(configuration_path));
	}
}