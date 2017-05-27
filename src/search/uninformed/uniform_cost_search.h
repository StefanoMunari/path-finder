/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

#include "../searchable.h"
#include "../../framework/problem/problem.h"
#include "../../framework/data/node_colored.h"
#include "../../framework/utils/node_comparator.h"
#include "../../utils/boost_types.h"
#include "../../utils/constants.h"
#include "../../utils/algorithm.h"
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <utility>// std::pair
#include <algorithm>// std::for_each
#include <climits>// UINT_MAX

using std::priority_queue;
using std::map;
using std::vector;
using std::string;

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class UniformCostSearch;

	template <typename State>
	class UniformCostSearch : public Searchable<State> {
	/*, Solve, Expand {*/
	  public:
	    UniformCostSearch(GraphPtr_IdMap static_graph) noexcept;
	    //virtual std::vector<Action>*
	    Node<State>* Search(GraphPtr_IdMap, const Problem<State>&);
	  private:
	  	/*
	    virtual std::vector<Action>* Solve(Node*);
	    virtual std::vector<Node>* Expand(Node*);
	    */
		priority_queue<
			std::pair<NodeColored<State>*, uint>,
			vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>>*
		_MakeQueue(State);
		map<string, std::pair<NodeColored<State>*, uint>>*
		_MakeSearchMap(State, map<int, string>*);
	    GraphPtr_IdMap _static_graph;
	};

	template <typename State>
	UniformCostSearch<State>::UniformCostSearch(GraphPtr_IdMap static_graph) noexcept{
		this->_static_graph = static_graph;
	};
/*
	use infrastructure_graph + costs_graph to initialize
	each Node. the Node abstraction is created at run-time.
	First State & Goal State (test) exist in problem
*/
	template <typename State>
	//std::vector<Action>*
	Node<State>*
	UniformCostSearch<State>::Search(GraphPtr_IdMap dynamic_graph_,
		const Problem<State>& problem){
		/* Boost-property accessors */
		IndexMap node_index =
			boost::get(boost::vertex_index, (*_static_graph.first));
		/* vars */
		Graph *static_graph = _static_graph.first;
		Graph *dynamic_graph = dynamic_graph_.first;
		map<string, int>* indexes_map = (map<string, int>*)_static_graph.second;
		auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
		auto contour = this->_MakeQueue(problem.GetFirstState());
		auto search_map = this->_MakeSearchMap(
			(contour->top()).first->state, &ids_map);
		VertexDescriptor current, end;
		end = boost::graph_traits<Graph>::null_vertex();
		/* body */
		while(!contour->empty() && (current != end)){
			auto current_node = contour->top();
			contour->pop();
			current = (*indexes_map)[current_node.first->state];
			if(problem.IsGoal(current_node.first->state))
				return current_node.first;/* goal reached */
			auto neighbors = boost::adjacent_vertices(current, *_static_graph.first);

			for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
				string neighbor = ids_map[node_index[*n_it]];
				auto current_neigh = (*search_map)[neighbor];
				if(current_neigh.first->color  ==  WHITE){
					current_neigh.first->color = GRAY;
					auto neigh_cost = current_node.second +
			   			(*static_graph)[boost::edge(current,*n_it,(*static_graph)).first] +
			   			(*dynamic_graph)[boost::edge(current,*n_it,(*dynamic_graph)).first];
			   		current_neigh.first->parent = current_node.first;
			   		current_neigh.second = neigh_cost;
			   		contour->push(current_neigh);
				}
			}
		}
		/* search failed */
		return nullptr;
	};

	template <typename State>
	priority_queue<
		std::pair<NodeColored<State>*, uint>,
		vector<std::pair<NodeColored<State>*, uint>>,
		NodeComparator<State, uint>
		>*
	UniformCostSearch<State>::_MakeQueue(State source_id) {
		/* shortcut for verbose type */
		typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
		/* declare local vars */
		auto source_node =
			SearchableTreeNode(
				new NodeColored<State>(source_id, nullptr, GRAY), 0);
		auto contour =
			new priority_queue<SearchableTreeNode, vector<SearchableTreeNode>,
			NodeComparator<State, uint>>();
		contour->push(source_node);
		return contour;
	};

	template <typename State>
	map<string, std::pair<NodeColored<State>*, uint>>*
	UniformCostSearch<State>::_MakeSearchMap(State source,
		map<int, string>* ids_map)
	{
		/* Boost-property accessors */
		IndexMap node_index =
			boost::get(boost::vertex_index, (*(_static_graph.first)));
		/* shortcut for verbose type */
		typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
		/* vars */
		auto search_map = new map<string, SearchableTreeNode>();
		auto vertexes = boost::vertices((*(_static_graph.first)));
		/* body */
		search_map->insert(
				std::pair<string, SearchableTreeNode>(
					source,
					SearchableTreeNode(
						new NodeColored<State>(source, nullptr, GRAY),0)));
		for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it)
			search_map->insert(
				std::pair<string, SearchableTreeNode>(
					(*ids_map)[node_index[*v_it]],
					SearchableTreeNode(
						new NodeColored<State>(
							(*ids_map)[node_index[*v_it]], nullptr, WHITE),
							UINT_MAX)));
		return search_map;
	}
}
#endif /*UNIFORM_COST_SEARCH_H*/