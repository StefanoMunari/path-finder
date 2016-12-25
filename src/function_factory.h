#ifndef FUNCTION_FACTORY_H
#define FUNCTION_FACTORY_H

#include <string>
#include <python2.7/Python.h>

namespace path_finder
{
	class FunctionFactory{
		public:
			FunctionFactory(PyObject *);
			~FunctionFactory();
			PyObject* CreateFunction(const std::string&);
			PyTupleObject* CreateArgument(const std::string&);
		private:
			PyObject* _module=nullptr;
	};
}

#endif /*FUNCTION_FACTORY_H*/