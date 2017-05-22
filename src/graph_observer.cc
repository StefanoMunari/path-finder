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

	GraphObserver::GraphObserver(const std::string & subject_dir){
		/* creating the INOTIFY instance */
		notifier = inotify_init();
		/* checking for error */
		if(notifier < 0)
			perror("inotify_init");
		/* add the directory to the watch list:
			- IN_CREATE : notify when a new file is created inside the subject*/
		subject=inotify_add_watch(notifier, subject_dir.c_str(), IN_CREATE);
	}

	GraphObserver::~GraphObserver(){
		/*removing the subject directory from the watch list*/
		inotify_rm_watch(notifier, subject);
		/*closing the INOTIFY instance*/
		close(notifier);
	}

	void GraphObserver::EventLoop(){
		/* Wait for changes in the subject.
		This read blocks until the change event occurs */
		char buffer [EVENT_BUF_LEN];
		int length=read(notifier, buffer, EVENT_BUF_LEN );
		/*checking for error*/
		if ( length < 0 )
			perror("inotify_read");
		/* read return the list of change events happens.
		   read the change event one by one and process it accordingly.*/
		for(int i=0; i < length;){
			struct inotify_event* event= (struct inotify_event *) &buffer[i];
			if((event->len) && (event->mask & IN_CREATE))
		      printf("New file %s created.\n", event->name);
		  	i+=EVENT_SIZE + event->len;
		}
	}
}
