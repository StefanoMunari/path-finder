/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef GRAPH_OBSERVER_H
#define GRAPH_OBSERVER_H

#include <string>
#include <sys/inotify.h>

namespace path_finder
{
	class GraphObserver{
		public:
			GraphObserver() =delete;
			GraphObserver(const std::string &);
			~GraphObserver();
		private:
			void EventLoop();
			int notifier;
			int subject;
	};
}

#endif /*GRAPH_OBSERVER_H*/