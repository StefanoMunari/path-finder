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
#include <string>

typedef boost::property<boost::vertex_name_t, std::string,
  boost::property<boost::vertex_index2_t, int>> VertexIndexProperty;
typedef boost::property<boost::edge_weight_t, unsigned int> EdgeWeigthProperty;
typedef boost::adjacency_list<boost::hash_setS,boost::hash_setS,boost::directedS,
VertexIndexProperty, EdgeWeigthProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;

#endif /*BOOST_TYPES_H*/