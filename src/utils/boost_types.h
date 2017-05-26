/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef BOOST_TYPES_H
#define BOOST_TYPES_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <map>
#include <string>

/* Internal Bundled Properties */
typedef int Index;
typedef unsigned int Weight;
/* Graph Type */
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS,
Index, Weight> Graph;
/* External Properties */
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
/* Graph Traits */
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
typedef boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;
/* Auxiliary Structures */
typedef std::map<std::string, VertexDescriptor> StringToVertexMap;

#endif /*BOOST_TYPES_H*/