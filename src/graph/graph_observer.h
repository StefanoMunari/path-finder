/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_OBSERVER_H
#define GRAPH_OBSERVER_H

#include "../utils/process_state.h"
#include <string>
#include <sys/inotify.h>

namespace path_finder
{
	class GraphObserver{
		public:
			GraphObserver() {};
			~GraphObserver();
			void Observe(const std::string &);
		private:
			void EventLoop();
			int _notifier;
			int _subject;
		    ProcessState _state = WAITING;
	};
}

#endif /*GRAPH_OBSERVER_H*/