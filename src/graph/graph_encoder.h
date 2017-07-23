/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_ENCODER_H
#define GRAPH_ENCODER_H

#include "../utils/boost_types.h"

namespace path_finder
{
	class GraphEncoder{
		public:
			GraphEncoder() noexcept {};
			GraphEncoder(const GraphEncoder& that) noexcept {};
			GraphEncoder& operator=(const GraphEncoder& that) noexcept
			{
				return *this;
			}
			~GraphEncoder() noexcept {};
			GraphPtr_IdMap
				Encode(
					std::map<std::string, std::vector<std::string>> *,
					std::map<std::string, std::vector<uint>> *)
				const;
	};
}

#endif /*GRAPH_ENCODER_H*/