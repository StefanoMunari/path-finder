namespace path_finder
{
	#ifndef FUNCTION_FACTORY_H
	#define FUNCTION_FACTORY_H

	class FunctionFactory{
		public:
			FunctionFactory(PyObject *);
			~FunctionFactory();
			PyObject* CreateFunction(const string&);
			PyTupleObject* CreateArgument(const string&);
		private:
			PyObject* _module=nullptr;
	};


	#endif /*FUNCTION_FACTORY_H*/
}