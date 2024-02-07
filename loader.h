#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*plugin_ptr_t)(CUIRect &View1, CUIRect &View2, CUIRect &View3);

CUIRect placeholder1;
CUIRect placeholder2;
CUIRect placeholder3;
CUIRect placeholder4;
CUIRect placeholder5;
CUIRect placeholder6;

void HotUi(
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
	plugin_ptr_t tick_ptr;
	tick_ptr = (plugin_ptr_t)dlsym(handle, "ui_tick");

	error = dlerror();
	if(error != NULL)
	{
		fprintf(stderr, "%s\n", error);
		return;
	}

	tick_ptr(View1, View2, View3, View4, View5, View6);

	dlclose(handle);
}
