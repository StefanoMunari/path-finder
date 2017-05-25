/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

#include "../../framework/problem/problem.h"
#include "../../framework/data/node_colored.h"
#include "../../framework/utils/node_comparator.h"
#include "../../utils/constants.h"
#include "../../utils/boost_types.h"
#include <queue>
#include <map>
#include <utility>// std::pair
#include <algorithm>// std::for_each
#include <climits>// UINT_MAX

typedef unsigned int uint;
typedef std::pair<NodeColored<State>*, uint> SearchTreeNode;

namespace path_finder
{
	template <typename State> class UniformCostSearch;

	template <typename State>
	class UniformCostSearch : public Search {
	/*, Solve, Expand {*/
	  public:
	    UniformCostSearch(Graph* static_graph) noexcept;
	    //virtual std::vector<Action>*
	    void Search(Problem*);
	  private:
	  	/*
	    virtual std::vector<Action>* Solve(Node*);
	    virtual std::vector<Node>* Expand(Node*);
	    */
		priority_queue<SearchTreeNode, NodeComparator>* _MakeQueue(Graph*, State);
	    Graph* _static_graph;
	};

	template <typename State>
	UniformCostSearch::UniformCostSearch(Graph* static_graph) noexcept{
		this->_static_graph=static_graph;
	};
/*
	use infrastructure_graph + costs_graph to initialize
	each Node. the Node abstraction is created at run-time.
	First State & Goal State (test) exist in problem
*/
	template <typename State>
	//std::vector<Action>*
	void
	UniformCostSearch<typename State>::Search(Graph* dynamic_graph, Problem* problem){
		auto contour=this->_MakeQueue(dynamic_graph, problem->GetFirstState());
	}

	priority_queue<SearchTreeNode, NodeComparator>*
	_MakeQueue(Graph* dynamic_graph, State source) {
		/* Boost-property accessors */
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*graph));
		boost::property_map<Graph, boost::edge_weight_t>::type
			edge_cost = boost::get(boost::edge_weight, (*graph));
		/* declare local vars */
		auto source_node=SearchTreeNode(new NodeColored(source, nullptr, GRAY), 0);
		auto contour=
			new priority_queue<SearchTreeNode, NodeComparator>();
		auto vertexes= boost::vertices((*_static_graph));
		auto neighbors= boost::adjacent_vertices(source, (*_static_graph));
		map<const string&, uint> vertex_map();
		/* body */
		contour->push(source_node);
		for(auto v_it= vertexes.first; v_it != vertexes.second; ++v_it)
			vertex_map.insert(std::pair<const string&, uint>(node_id[*v_it], UINT_MAX));
		for (auto n_it = neighbors.first; n_it != neighbors.second; ++n_it){
			contour->push(SearchTreeNode(
					new NodeColored(vertex_map[node_id[*n_it]], nullptr, WHITE),
		   			edge_cost[boost::edge(*v_it,*n_it,(*static_graph)).first] +
		   			edge_cost[boost::edge(*v_it,*n_it,(*dynamic_graph)).first]));
			vertex_map.erase(node_id[*n_it]);
		}
		for(auto const &map_pair : vertex_map)
			contour->push(
				SearchTreeNode(new NodeColored(map_pair.first, nullptr, WHITE)),
				map_pair.second);
		return contour;
	}
}
#endif /*UNIFORM_COST_SEARCH_H*/