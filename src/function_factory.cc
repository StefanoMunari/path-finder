#include "function_factory.h"

using std::string;

namespace path_finder
{
	FunctionFactory::FunctionFactory(PyObject *module){
		_module=module;
	}
	FunctionFactory::~FunctionFactory(){
		Py_DECREF(_module);
	}

	PyObject* FunctionFactory::CreateFunction(const string& function_name){
		PyObject *function=nullptr;
		if(_module != nullptr)
			function=PyObject_GetAttrString(_module, function_name.c_str());
		return function;
	}

	PyTupleObject* FunctionFactory::CreateArgument(const string& file_path){
	    PyObject* argument=PyTuple_New(1);
	    PyTuple_SetItem(argument, 0, PyString_FromString(file_path.c_str()));
	    return argument;
	}
}