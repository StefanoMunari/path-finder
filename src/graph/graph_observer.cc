/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "graph_observer.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

using std::string;

namespace path_finder
{
	#define EVENT_SIZE	( sizeof (struct inotify_event) )
	#define EVENT_BUF_LEN	( 1024 * ( EVENT_SIZE + 16 ) )

	GraphObserver::~GraphObserver(){
		_state = STOPPED;
		while(_state !=  TERMINATED){};
		/*removing the _subject directory from the watch list*/
		inotify_rm_watch(_notifier, _subject);
		/*closing the INOTIFY instance*/
		close(_notifier);
	}

	void GraphObserver::Observe(const std::string & _subject_dir){
		/* creating the INOTIFY instance */
		_notifier = inotify_init();
		/* checking for error */
		if(_notifier < 0)
			perror("inotify_init");
		/* add the directory to the watch list:
			- IN_CREATE : notify when a new file is created inside the _subject*/
		_subject = inotify_add_watch(_notifier, _subject_dir.c_str(),
			IN_CREATE | IN_MOVED_TO);
		_state = READY;
		this->EventLoop();
	}

	void GraphObserver::EventLoop(){
		_state = RUNNING;
		/* Wait for changes in the _subject.
		This read blocks until the change event occurs */
		char buffer [EVENT_BUF_LEN];
		while(_state  ==  RUNNING){
			int length = read(_notifier, buffer, EVENT_BUF_LEN );
			/*checking for error*/
			if ( length < 0 )
				perror("inotify_read");
			/* read return the list of change events happens.
			   read the change event one by one and process it accordingly.*/
			for(int i =0; i < length;){
				struct inotify_event* event = (struct inotify_event *) &buffer[i];
				if((event->len) && ((event->mask & IN_CREATE) || (event->mask & IN_MOVED_TO)))
			      printf("New file %s created.\n", event->name);/* TODO: set action */
			  	i+= EVENT_SIZE + event->len;
			}
		}
		_state = TERMINATED;
	}
}
