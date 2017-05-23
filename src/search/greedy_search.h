/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include <queue>
#include <vector>
#include <algorithm> // std::for_each
#include "../constants.h"

namespace path_finding
{
	template <typename State> class GreedySearch;

	template <typename State>
	class GreedySearch: public Search, Solve, Expand {
	  public:
	    virtual std::vector<Action>* search(Problem*);
	    virtual std::vector<Action>* solve(Node*);
		/* TODO: Expand is a strategy Node, not a method */
	    virtual std::vector<Node>* expand(Node*);
	};

	template <typename State>
	GreedySearch<typename State>::search(Problem* problem){
		using std::priority_queue;
		using std::vector;
		using std::for_each;
		priority_queue<Node*> contour= priority_queue<Node*>();
		contour.push(problem->getFirstState());
		Node* node= nullptr;
		vector<Node>* children= nullptr;
		while(true){
			if(contour.empty())
			  return EMPTY;
			node= contour.pop();
			if((problem->getGoalTest->isTest(node->getState())) == true)
			  return solve(node);
			children= expand(node);
			for_each(children->begin(), children->end(),
			  [](Node child_node){
			    /*
			    using priority queue an ordering strategy is defined
			    by the data structure at "push-time"
			    */
			    contour.push(child_node);
			  });
		}
	};
}
#endif /*GREEDY_SEARCH_H*/