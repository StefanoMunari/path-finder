/**
 * @file
 * @brief  Contains costs related to informed search.
 * @author <stefanomunari.sm@gmail.com>
 *
 * The costs refer to the current node:
 * 	g is the effective cost from source to the current node
 * 	h is the estimated cost from goal to the current node
 */
#ifndef NODE_COSTS_H
#define NODE_COSTS_H

#include "../../../utils/types.h"
#include <climits>// UINT_MAX

namespace path_finder
{

class NodeCosts{
	public:
		NodeCosts() noexcept
		: g(UINT_MAX), h(UINT_MAX) {}
		NodeCosts(const NodeCosts& nc) noexcept
		{
			this->h = nc.h;
			this->g = nc.g;
		}
		NodeCosts& operator=(const NodeCosts& nc) noexcept
		{
			this->h = nc.h;
			this->g = nc.g;
			return (*this);
		}
		~NodeCosts() noexcept {};
		bool operator >(const NodeCosts& nc) const noexcept
		{
			unsigned long f0 = this->g + this->h;
			unsigned long f1 = nc.g + nc.h;
			return f0>f1;
		}
		/*
		 * effective cost (source, n)
		 */
		uint g;
		/*
		 * estimated cost (goal, n)
		 */
		uint h;
};

}
#endif /*NODE_COSTS_H*/