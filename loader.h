#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <limits.h>
#include <poll.h>
#include <time.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>

#define HOT_SO_PATH "../../ddnet_hotui/sample.so"

#define READ_ONLY_OPERATION	(IN_ACCESS | IN_OPEN | IN_CLOSE_NOWRITE)

int last_so_update_time = -1;
int inotify_fd = -1;
int inotify_watch = -1;

int add_watch()
{
	// allow calling it multiple times without breaking it
	if(inotify_fd == -1)
		inotify_fd = inotify_init ();
	if (inotify_fd == -1)
	{
		dbg_msg("ddnet_hotui", "Error: failed to init inotify fd");
		exit(1);
	}

	// inotify can only watch files that exist
	// so while it is delted we just wait
	if (access(HOT_SO_PATH, F_OK) != 0)
	{
		dbg_msg("ddnet_hotui", "waiting for %s to appear ...", HOT_SO_PATH);
		// we already listen for deletion of the file
		// but seems like that is not catching every swap `make` triggers
		inotify_watch = -1;
		return 0;
	}

	// struct stat attr;
	// if(stat(HOT_SO_PATH, &attr))
	// {
	// 	dbg_msg("ddnet_hotui", "failed to get stats for %s", HOT_SO_PATH);
	// 	return;
	// }
	// int time = attr.st_mtime;
	// if(time > last_so_update_time)
	// {
	// 	// force reload if the date updated
	// 	// we already check with inotify but it does not seem to work
	// 	// every time
	// 	inotify_watch = -1;
	// 	last_so_update_time = time;
	// }

	if(inotify_watch != -1)
		return 0;

	// when i compiled the so file and listening for all events
	// i got back in this order
	// IN_ATTRIB (4), IN_DELETE_SELF (1024), IN_IGNORED (32768)
	// so lets only listen for the last one
	inotify_watch = inotify_add_watch (inotify_fd, HOT_SO_PATH, IN_IGNORED);
	if (inotify_watch == -1)
	{
		dbg_msg("ddnet_hotui", "Error: failed watch using inotify");
		exit(1);
	}

	printf("Watching %s using inotify_watch %d\n", HOT_SO_PATH, inotify_watch);
	return 1;
}

int got_new_so()
{
	add_watch();
	if(inotify_fd == -1)
		return 1;
	struct pollfd poll_fd;
	poll_fd.fd = inotify_fd;

	poll_fd.events = POLLIN;
	poll_fd.revents = 0;
	int a = poll(&poll_fd, 1, 0);
	dbg_msg("ddnet_hotui", "polling ...");
	if(a == 0)
		return 0;
	if(a < 0)
	{
		dbg_msg("ddnet_hotui", "poll returned %d", a);
		return 0;
	}
	// TODO: we do not really care what we read here
	//       but we have to consume the event
	//       there has to be a way to do so without reading
	char aBuf[10 * (sizeof(struct inotify_event))];
	int num_read = read(poll_fd.fd, aBuf, sizeof(aBuf));
	dbg_msg("ddnet_hotui", "num_read=%d", num_read);
	if(num_read < 1)
	{
		dbg_msg("ddnet_hotui", "bad num_read=%d", num_read);
		exit(1);
	}
	int got_update = 0;
	for (char *p = aBuf; p < aBuf + num_read; ) {
		struct inotify_event *pEvent = (struct inotify_event *) p;
		dbg_msg("ddnet_hotui", "got event with mask %d", pEvent->mask);
		// file deleted
		if(pEvent->mask & IN_IGNORED)
		{
			// cleanup watch of dead inode
			inotify_rm_watch(inotify_fd, inotify_watch);
			// triggers reconnect if it appears again
			inotify_watch = -1;
			dbg_msg("ddnet_hotui", "file deleted %s", HOT_SO_PATH);
			got_update = 1;
		}
		else if(pEvent->mask & READ_ONLY_OPERATION)
		{
			// we call stat() on the file our self
			// this is not considered an update
		}
		else
		{
			dbg_msg("ddnet_hotui", "reloading because of inotify mask %d", pEvent->mask);
			got_update = 1;
		}

		p += sizeof(struct inotify_event) + pEvent->len;
	}

	return got_update;
}


class CEditor;

typedef void (*cui_rects_ptr_t)(
	CUIRect &View1,
	CUIRect &View2,
	CUIRect &View3,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6);

CUIRect placeholder1;
CUIRect placeholder2;
CUIRect placeholder3;
CUIRect placeholder4;
CUIRect placeholder5;
CUIRect placeholder6;

void HotCuiRects(
	CUIRect &View1 = placeholder1,
	CUIRect &View2 = placeholder2,
	CUIRect &View3 = placeholder3,
	CUIRect &View4 = placeholder4,
	CUIRect &View5 = placeholder5,
	CUIRect &View6 = placeholder6)
{
	char *error;
	void *handle = dlopen(HOT_SO_PATH, RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		return;
	}

	dlerror();
	cui_rects_ptr_t tick_ptr;
	tick_ptr = (cui_rects_ptr_t)dlsym(handle, "hot_cui_rects");

	error = dlerror();
	if(error != NULL)
	{
		fprintf(stderr, "%s\n", error);
		return;
	}

	tick_ptr(View1, View2, View3, View4, View5, View6);

	dlclose(handle);
}

typedef void (*editor_cui_rects_ptr_t)(
	CEditor *pEditor,
	CUIRect &View1,
	CUIRect &View2,
	CUIRect &View3,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6);
editor_cui_rects_ptr_t tick_ptr = nullptr;
void *handle = nullptr;

void HotEditorCuiRects(
	CEditor *pEditor = nullptr,
	CUIRect &View1 = placeholder1,
	CUIRect &View2 = placeholder2,
	CUIRect &View3 = placeholder3,
	CUIRect &View4 = placeholder4,
	CUIRect &View5 = placeholder5,
	CUIRect &View6 = placeholder6)
{
	if(got_new_so())
	{
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		dbg_msg("ddnet_hotui", "X ddnet_hotui - reloading ... X");
		printf("X inotify: %s            X\n", inotify_fd == -1 ? "ERROR  " : "RUNNING");
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		char *error;
		if (handle)
			dlclose(handle);
		handle = dlopen(HOT_SO_PATH, RTLD_LAZY);
		if(!handle)
		{
			fprintf(stderr, "%s\n", dlerror());
			tick_ptr = nullptr;
			return;
		}

		dlerror();
		tick_ptr = (editor_cui_rects_ptr_t)dlsym(handle, "editor_hot_cui_rects");

		error = dlerror();
		if(error != NULL)
		{
			fprintf(stderr, "%s\n", error);
			dlclose(handle);
			tick_ptr = nullptr;
			return;
		}
	}

	if(!tick_ptr)
		return;

	tick_ptr(pEditor, View1, View2, View3, View4, View5, View6);
}
