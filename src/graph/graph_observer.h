/**
 * @file
 * @brief	It watches a subject folder. This folder will contain the info
 *			on the new graph costs. It notifies the GraphRegistry when a new
 *			file is added to the subject folder. It is a singleton class.
 * @details It uses inotify to monitor filesys events and std::thread for the
 *			event loop.
 * @author	<stefanomunari.sm@gmail.com>
 * @see	graph_registry.h
 * @see process_state.h
 */
#ifndef GRAPH_OBSERVER_H
#define GRAPH_OBSERVER_H

#include "../utils/process_state.h"
#include <string>
#include <thread>
#include <sys/inotify.h>

namespace path_finder
{
	class GraphObserver final {
		public:
			static GraphObserver& Instance(void);
			static void Observe(const std::string &);
		private:
			GraphObserver(void);
			GraphObserver(const GraphObserver&);
			GraphObserver& operator= (const GraphObserver&);
			~GraphObserver(void) noexcept;
			void EventLoop(void);
			static GraphObserver _instance;
			std::thread _executor;
			int _notifier;
			int _subject;
			std::string _subject_name;
		    ProcessState _state = WAITING;
	};
}

#endif /*GRAPH_OBSERVER_H*/