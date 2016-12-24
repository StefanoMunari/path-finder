namespace path_finder
{
	#ifndef AI_H
	#define AI_H

	//#define ID std::string

	class AI{
		public:
			AI* Instance(vector<string>&, map<string, vector<string>>&);
		protected:
			AI(vector<string>&, map<string, vector<string>>&);
			//List<ID> find_path();
		private:
			static AI* _ai;
			static GraphRegistry _registry;
			//static PathFinder _path_finder;
	};

	#endif /*AI_H*/
}