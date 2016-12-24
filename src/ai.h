#ifndef AI_H
#define AI_H

#include "graph_registry.h"
#include <map>
#include <vector>
#include <string>

namespace path_finder
{
	class AI{
		public:
			static AI* Instance(std::vector<std::string>&, 
				std::map<std::string, std::vector<std::string>>&);
		protected:
			AI(std::vector<std::string>&, 
				std::map<std::string, std::vector<std::string>>&);
			//List<ID> find_path();
		private:
			static AI* _ai;
			static GraphRegistry _registry;
			//static PathFinder _path_finder;
	};
}

#endif /*AI_H*/