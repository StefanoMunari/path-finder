/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "function_factory.h"

using std::string;

namespace path_finder
{
	FunctionFactory::FunctionFactory(PyObject* module){
		this->_module=module;
	}

	FunctionFactory::~FunctionFactory(){
		Py_DECREF(_module);
	}

	PyObject* FunctionFactory::CreateFunction(const string& function_name){
		PyObject *function=nullptr;
		if(this->_module != nullptr)
			function=PyObject_GetAttrString(this->_module,
				function_name.c_str());
		return function;
	}

	PyObject* FunctionFactory::CreateArgument(const string& file_path){
	    PyObject* argument=PyTuple_New(1);
	    PyTuple_SetItem((PyObject*)argument, 0, PyString_FromString(file_path.c_str()));
	    return argument;
	}
}