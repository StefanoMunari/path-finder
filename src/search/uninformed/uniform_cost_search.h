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
#include "../../utils/constants.h"
#include "../../utils/boost_types.h"
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
	    UniformCostSearch(Graph* static_graph) noexcept;
	    //virtual std::vector<Action>*
	    Node<State>* Search(Graph*, const Problem<State>&);
	  private:
	  	/*
	    virtual std::vector<Action>* Solve(Node*);
	    virtual std::vector<Node>* Expand(Node*);
	    */
		priority_queue<
			std::pair<NodeColored<State>*, uint>,
			vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>>*
		_MakeQueue(Graph*, State);
		map<string, std::pair<NodeColored<State>*, uint>>*
		_MakeSearchMap(State source);
	    Graph* _static_graph;
	};

	template <typename State>
	UniformCostSearch<State>::UniformCostSearch(Graph* static_graph) noexcept{
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
	UniformCostSearch<State>::Search(Graph* dynamic_graph,
		const Problem<State>& problem){
		/* Boost-property accessors */
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*dynamic_graph));
		boost::property_map<Graph, boost::edge_weight_t>::type
			edge_cost = boost::get(boost::edge_weight, (*dynamic_graph));
		/* vars */
		auto contour = this->_MakeQueue(dynamic_graph, problem.GetFirstState());
		auto search_map = this->_MakeSearchMap((contour->top()).first->state);
		int counter =0;
		/* body */
		while(!contour->empty()){
			auto current_node = contour->top();
			contour->pop();
			if(problem.IsGoal(current_node.first->state))
				return current_node.first;/* search success */
			auto vertexes = boost::vertices((*_static_graph));
			VertexIterator current_it;
			VertexDescriptor vdescr = VertexDescriptor((void*)&current_node.first->state);
			auto neighbors = boost::adjacent_vertices(vdescr, (*_static_graph));
			/*
			auto v_it = vertexes.first;
			auto neighbors = boost::adjacent_vertices(*v_it, (*_static_graph));
			do{
				while(v_it !=  vertexes.second){
					if(node_id[*v_it]  ==  current_node.first->state){
						cout<<"found match "<<endl;
						current_it = v_it;
						break;
					}
					++v_it;
				}
				neighbors = boost::adjacent_vertices(*current_it, (*_static_graph));
			}while(neighbors.first  ==  neighbors.second);
			for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
				cout<<"NEIGH = "<<counter<<" -> "<<node_id[*n_it]<<endl;
				string neighbor = node_id[*n_it];
				auto current_neigh = (*search_map)[neighbor];
				cout<<"NEIGH-ID = "<<current_neigh.first->state<<endl;
				if(current_neigh.first->color  ==  WHITE){
					cout<<"NEIGH-WHITE "<<endl;
					current_neigh.first->color = GRAY;
					auto neigh_cost = current_node.second+
			   			edge_cost[boost::edge(*current_it,*n_it,(*_static_graph)).first] +
			   			edge_cost[boost::edge(*current_it,*n_it,(*dynamic_graph)).first];
			   		current_neigh.first->parent = current_node.first;
			   		current_neigh.second = neigh_cost;
			   		contour->push(current_neigh);
				}
			}
			++counter;
			*/
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
	UniformCostSearch<State>::_MakeQueue(Graph* dynamic_graph, State source_id) {
		/* shortcut for verbose type */
		typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
		/* Boost-property accessors */
		/*
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*_static_graph));
		boost::property_map<Graph, boost::edge_weight_t>::type
			edge_cost = boost::get(boost::edge_weight, (*_static_graph));
		*/
		/* declare local vars */
		auto source_node = SearchableTreeNode(new NodeColored<State>(source_id, nullptr, GRAY), 0);
		auto contour =
			new priority_queue<SearchableTreeNode, vector<SearchableTreeNode>,
			NodeComparator<State, uint>>();
		/*
		VertexIterator source_it;
		auto vertexes = boost::vertices((*_static_graph));
		for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
			if(node_id[*v_it]  ==  source_id){
				source_it = v_it;
				break;
			}
		}
		auto neighbors = boost::adjacent_vertices(*source_it, (*_static_graph));
		cout<<"Head"<<endl;
		for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
			vertex_map.insert(std::pair<string, uint>((string) node_id[*v_it], UINT_MAX));
		}
		cout<<"--COUNTOUR - START--"<<endl;
		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			cout<<"--COUNTOUR--"<<endl;
			contour->push(SearchableTreeNode(
					new NodeColored<State>(node_id[*n_it], source_node.first, GRAY),
		   			edge_cost[boost::edge(*source_it,*n_it,(*_static_graph)).first] +
		   			edge_cost[boost::edge(*source_it,*n_it,(*dynamic_graph)).first]));
			vertex_map.erase((string) node_id[*n_it]);
		}*/
		contour->push(source_node);
		return contour;
	};

	template <typename State>
	map<string, std::pair<NodeColored<State>*, uint>>*
	UniformCostSearch<State>::_MakeSearchMap(State source)
	{
		/* Boost-property accessors */
		boost::property_map<Graph, boost::vertex_name_t>::type
			node_id = boost::get(boost::vertex_name, (*_static_graph));
		/* shortcut for verbose type */
		typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
		/* vars */
		auto search_map = new map<string, SearchableTreeNode>();
		auto vertexes = boost::vertices((*_static_graph));
		/* body */
		search_map->insert(
				std::pair<string, SearchableTreeNode>(
					source,
					SearchableTreeNode(
						new NodeColored<State>(source, nullptr, GRAY),
						0)));
		for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
			search_map->insert(
				std::pair<string, SearchableTreeNode>(
					(string) node_id[*v_it],
					SearchableTreeNode(
						new NodeColored<State>((string) node_id[*v_it], nullptr, WHITE),
						UINT_MAX)));
		}
		return search_map;
	}
}
#endif /*UNIFORM_COST_SEARCH_H*/