/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include <mutex>  // std::unique_lock
#include <condition_variable>

namespace path_finder
{

	#ifndef TERMINATION
	static std::mutex termination;
	#endif

	#ifndef WAIT_FOR_TERMINATION
	static std::condition_variable wait_for_termination;
	#endif
}