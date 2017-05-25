/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

#include <queue>
#include <vector>
#include <map>
#include <algorithm> // std::for_each
#include <climits>
#include "../../framework/problem/action.h"
#include "../../framework/node_colored.h"
#include "../../utils/constants.h"
#include "../../utils/boost_types.h"

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class UniformCostSearch;

	template <typename State>
	class UniformCostSearch {
	/*public Search, Solve, Expand {*/
	  public:
	    UniformCostSearch(Graph* static_graph) noexcept;
	    virtual std::vector<Action>* Search(Problem*);
	  private:
	  	/*
	    virtual std::vector<Action>* Solve(Node*);
	    virtual std::vector<Node>* Expand(Node*);
	    */
		priority_queue<NodeColored<State, uint>*>* _MakeQueue(Graph*, State);
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
	std::vector<Action>*
	UniformCostSearch<typename State>::Search(Graph* dynamic_graph, Problem* problem){
		auto contour=this->_MakeQueue(dynamic_graph, problem->GetFirstState());
	}

	priority_queue<NodeColored<State, uint>*>*
	_MakeQueue(Graph* dynamic_graph, State source) {
		/* Boost-property accessors */
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*graph));
		boost::property_map<Graph, boost::edge_weight_t>::type
			edge_cost = boost::get(boost::edge_weight, (*graph));
		/* declare local vars */
		auto contour= new priority_queue<NodeColored<State, int>*>();
		auto vertexes= boost::vertices((*_static_graph));
		auto neighbors= boost::adjacent_vertices(source, (*_static_graph));
		map<NodeColored<State>, uint> vertex_map();
		for(auto v_it= vertexes.first; v_it != vertexes.second; ++v_it)
			vertex_map.insert(
				std::pair<NodeColored<State>,uint>(node_id[*v_it],UINT_MAX));
		for (auto n_it = neighbors.first; n_it != neighbors.second; ++n_it){
			contour->push(vertex_map[node_id[*n_it]],
		   			edge_cost[boost::edge(*v_it,*n_it,(*static_graph)).first] +
		   			edge_cost[boost::edge(*v_it,*n_it,(*dynamic_graph)).first]);
			vertex_map.erase(node_id[*n_it]);
		}
		for(auto const &mpair : vertex_map)
			contour->push(mpair.first, mpair.second);
		return contour;
	}
}
#endif /*UNIFORM_COST_SEARCH_H*/