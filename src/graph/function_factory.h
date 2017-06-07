/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef FUNCTION_FACTORY_H
#define FUNCTION_FACTORY_H

#include <memory>
#include <string>
#include <python2.7/Python.h>

namespace path_finder
{
	class FunctionFactory{
		public:
			FunctionFactory() {};
			FunctionFactory(PyObject*);
			FunctionFactory(const FunctionFactory&);
			FunctionFactory& operator=(const FunctionFactory&);
			~FunctionFactory() noexcept {};
			PyObject* CreateFunction(const std::string&);
			PyObject* CreateArgument(const std::string&);
		private:
			std::shared_ptr<PyObject> _module = nullptr;
	};
}

#endif /*FUNCTION_FACTORY_H*/