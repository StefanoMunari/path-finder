/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include <shared_mutex>

namespace path_finder
{

#ifndef MUTEX_GRAPH
#define MUTEX_GRAPH
static std::shared_mutex G_mutex_graph;
#endif

}