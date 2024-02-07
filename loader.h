#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*plugin_ptr_t)(CUIRect &View);

void HotUi(CUIRect &View)
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

	tick_ptr(View);

	dlclose(handle);
}

