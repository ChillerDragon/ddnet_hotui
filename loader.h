#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

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
	void *handle = dlopen("../../ddnet_hotui/sample.so", RTLD_LAZY);
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

void HotEditorCuiRects(
	CEditor *pEditor = nullptr,
	CUIRect &View1 = placeholder1,
	CUIRect &View2 = placeholder2,
	CUIRect &View3 = placeholder3,
	CUIRect &View4 = placeholder4,
	CUIRect &View5 = placeholder5,
	CUIRect &View6 = placeholder6)
{
	char *error;
	void *handle = dlopen("../../ddnet_hotui/sample.so", RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		return;
	}

	dlerror();
	editor_cui_rects_ptr_t tick_ptr;
	tick_ptr = (editor_cui_rects_ptr_t)dlsym(handle, "editor_hot_cui_rects");

	error = dlerror();
	if(error != NULL)
	{
		fprintf(stderr, "%s\n", error);
		return;
	}

	tick_ptr(pEditor, View1, View2, View3, View4, View5, View6);

	dlclose(handle);
}

CListBox placeholderListBox1;

typedef void (*editor_list_cui_rects_ptr_t)(
	CEditor *pEditor,
	CListBox &ListBox,
	CUIRect &View1,
	CUIRect &View2,
	CUIRect &View3,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6);

void HotEditorListCuiRects(
	CEditor *pEditor = nullptr,
	CListBox &ListBox1 = placeholderListBox1,
	CUIRect &View1 = placeholder1,
	CUIRect &View2 = placeholder2,
	CUIRect &View3 = placeholder3,
	CUIRect &View4 = placeholder4,
	CUIRect &View5 = placeholder5,
	CUIRect &View6 = placeholder6)
{
	char *error;
	void *handle = dlopen("../../ddnet_hotui/sample.so", RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		return;
	}

	dlerror();
	editor_list_cui_rects_ptr_t tick_ptr;
	tick_ptr = (editor_list_cui_rects_ptr_t)dlsym(handle, "editor_list_hot_cui_rects");

	error = dlerror();
	if(error != NULL)
	{
		fprintf(stderr, "%s\n", error);
		return;
	}

	tick_ptr(pEditor, ListBox1, View1, View2, View3, View4, View5, View6);

	dlclose(handle);
}
