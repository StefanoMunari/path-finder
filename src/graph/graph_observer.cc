/*
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
*/
#include "graph_observer.h"
#include "graph_registry.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

using std::string;

namespace path_finder
{

#define EVENT_SIZE	( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN	( 1024 * ( EVENT_SIZE + 16 ) )

GraphObserver GraphObserver::_instance = GraphObserver();

GraphObserver& GraphObserver::Instance(void) noexcept
{
	return GraphObserver::_instance;
}

void GraphObserver::Observe(const std::string & _subject_dir)
{
	if(GraphObserver::_instance._state == WAITING){
		// creating the INOTIFY instance
		GraphObserver::_instance._notifier = inotify_init();
		// checking for error
		if(GraphObserver::_instance._notifier < 0)
			perror("inotify_init");
		// add the directory to the watch list:
		// - IN_CREATE : notify when a new file
		// is created inside the GraphObserver::_instance._subject
		// - IN_MOVED_TO : notify when a file is moved inside the
		// GraphObserver::_instance._subject
		GraphObserver::_instance._subject =
			inotify_add_watch(
				GraphObserver::_instance._notifier,
				_subject_dir.c_str(),
				IN_CREATE | IN_MOVED_TO);
		GraphObserver::_instance._subject_name = _subject_dir;
		GraphObserver::_instance._state = READY;
		GraphObserver::_instance._executor =
			std::thread([]() {
				GraphObserver::_instance.EventLoop();
			});
	}
}

GraphObserver::GraphObserver(void) noexcept {}

GraphObserver::GraphObserver(const GraphObserver& that) noexcept
{
	// since it is static class this body is empty/not needed*/
}

GraphObserver& GraphObserver::operator= (const GraphObserver&) noexcept
{
	// since it is static class this body is empty/not needed*/
	return GraphObserver::_instance;
}

GraphObserver::~GraphObserver(void) noexcept
{
	GraphObserver::_instance._state = STOPPED;
	GraphObserver::_instance._executor.join();
	//removing the _subject directory from the watch list*/
	inotify_rm_watch(
		GraphObserver::_instance._notifier,
		GraphObserver::_instance._subject);
	// closing the INOTIFY instance*/
	close(GraphObserver::_instance._notifier);
}

void GraphObserver::EventLoop(void)
{
	GraphObserver::_instance._state = RUNNING;
	// Wait for changes in the GraphObserver::_instance._subject.
	// This read blocks until th* change event occurs
	char buffer [EVENT_BUF_LEN];
	while(GraphObserver::_instance._state  ==  RUNNING){
		int length =
			read(GraphObserver::_instance._notifier, buffer, EVENT_BUF_LEN);
		//checking for error*/
		if ( length < 0 )
			perror("inotify_read");
		// read return the list of change events happens.
		//  read the change event one by one and process it accordingly.
		//  It hangs up until a new event happens
		for(int i =0; i < length;){
			struct inotify_event* event =
				(struct inotify_event *) &buffer[i];
			if((event->len) &&
				((event->mask & IN_CREATE) ||
				(event->mask & IN_MOVED_TO)))
			{
				GraphRegistry::Instance().UpdateDynamicRegistry(
					GraphObserver::_instance._subject_name,
					event->name);
			}
		  	i += EVENT_SIZE + event->len;
		}
	}
	GraphObserver::_instance._state = TERMINATED;
}

}
