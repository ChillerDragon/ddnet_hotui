#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define HOT_SO_PATH "../../ddnet_hotui/sample.so"

class CEditor;

__int64_t last_so_create_time = -1;

int got_update()
{
	struct stat info;
	if(stat(HOT_SO_PATH, &info))
	{
		dbg_msg("ddnet_hotui", "failed to get stats of %s", HOT_SO_PATH);
		return 1;
	}

	__int64_t time = info.st_ctime;
	if(time > last_so_create_time)
	{
		last_so_create_time = time;
		return 1;
	}
	return 0;
}

/*
 * cui rects
 */

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

/*
 * editor cui rects
 */

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
	if(got_update())
	{
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		dbg_msg("ddnet_hotui", "X ddnet_hotui detected update ...  X");
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		char *error;
		if (handle)
			dlclose(handle);
		handle = dlopen(HOT_SO_PATH, RTLD_LAZY);
		if(!handle)
		{
			fprintf(stderr, "%s\n", dlerror());
			tick_ptr = nullptr;
			last_so_create_time = -1;
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
			last_so_create_time = -1;
			return;
		}
	}

	if(!tick_ptr)
		return;

	tick_ptr(pEditor, View1, View2, View3, View4, View5, View6);
}

/*
 * hot void
 */

typedef void (*hot_void_ptr_t)(
	void *void1, size_t size1,
	void *void2, size_t size2,
	void *void3, size_t size3,
	void *void4, size_t size4,
	void *void5, size_t size5,
	void *void6, size_t size6);
hot_void_ptr_t void_tick_ptr = nullptr;
void *void_handle = nullptr;

void HotVoidPtrs(
	void *void1 = nullptr, size_t size1 = 0,
	void *void2 = nullptr, size_t size2 = 0,
	void *void3 = nullptr, size_t size3 = 0,
	void *void4 = nullptr, size_t size4 = 0,
	void *void5 = nullptr, size_t size5 = 0,
	void *void6 = nullptr, size_t size6 = 0)
{
	if(got_update())
	{
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		dbg_msg("ddnet_hotui", "X ddnet_hotui detected update ...  X");
		dbg_msg("ddnet_hotui", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		char *error;
		if (void_handle)
			dlclose(void_handle);
		void_handle = dlopen(HOT_SO_PATH, RTLD_LAZY);
		if(!void_handle)
		{
			fprintf(stderr, "%s\n", dlerror());
			void_tick_ptr = nullptr;
			last_so_create_time = -1;
			return;
		}

		dlerror();
		void_tick_ptr = (hot_void_ptr_t)dlsym(void_handle, "hot_void_ptrs");

		error = dlerror();
		if(error != NULL)
		{
			fprintf(stderr, "%s\n", error);
			dlclose(void_handle);
			void_tick_ptr = nullptr;
			last_so_create_time = -1;
			return;
		}
	}

	if(!void_tick_ptr)
		return;

	void_tick_ptr(
		void1, size1,
		void2, size2,
		void3, size3,
		void4, size4,
		void5, size5,
		void6, size6);
}

