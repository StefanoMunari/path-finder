/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "ai.h"
#include "graph/graph_observer.h"
#include <stdexcept>

using std::string;

namespace path_finder
{

AI::AI(
	const string& path, const string& f_name_prefix, const string& f_extension)
{
	this->_category = f_name_prefix;

   try
   {
	GraphRegistry::Instance().InsertGraph(
		f_name_prefix, path+f_name_prefix, f_extension);
   }
   catch (const std::exception& exc)
   {// propagate exception
      throw;
   }

	GraphObserver::Instance().Observe(path);
}

#ifdef DEBUG
void AI::Print(void)
const noexcept
{
	GraphRegistry::Instance().PrintGraph(
		*(GraphRegistry::Instance().GetDynamicGraph(_category)));
}
#endif /*DEBUG*/

}