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

class GraphObserver final
{
	public:
		static GraphObserver& Instance(void) noexcept;
		static void Observe(const std::string &);
		static void Finalize(void) noexcept;
	private:
		GraphObserver(void) noexcept;
		GraphObserver(const GraphObserver&) noexcept;
		GraphObserver& operator= (const GraphObserver&) noexcept;
		~GraphObserver(void) noexcept;
		void ChangeState(ProcessState);
		void EventLoop(void);
	private:
		static GraphObserver _instance;
		std::thread _executor;
		int _notifier;
		int _subject;
		std::string _subject_name;
	   ProcessState _state = WAITING;
};

}
#endif /*GRAPH_OBSERVER_H*/