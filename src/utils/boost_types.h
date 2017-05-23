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

typedef boost::property<boost::vertex_index_t,  int> VertexIndexProperty;
typedef boost::property<boost::edge_weight_t, int> EdgeWeigthProperty;
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS,
VertexIndexProperty,EdgeWeigthProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;


#endif /*BOOST_TYPES_H*/