# ddnet_hotui
Snippets of code of me playing with ddnet CUIRects

Add this to the top of your ddnet client code C++ file
```C++
#include <cstring>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*plugin_ptr_t)(CUIRect &View);
```

And this in the method where you want to do hot reloading
```C++
// void CMenus::RenderSettings(CUIRect MainView)
// {
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

	tick_ptr(MainView);

	dlclose(handle);
// }
```

Also when compiling ddnet you need to make sure the ``-rdynamic`` flag is set.
So somewhere in your CMakeLists.txt add this line
```cmake
add_cxx_compiler_flag_if_supported(OUR_FLAGS_LINK -rdynamic)
```

Then you can play around in the ``sample.cpp`` file and run ``make`` when you are done. If the path here ``void *handle = dlopen("../../ddnet_hotui/sample.so", RTLD_LAZY);`` is correct you should see instant ui changes in your running client.

A sample implementation can we seen [here](https://github.com/ChillerDragon/ddnet/commit/95695caadde37c4201c01c5c8d08f2068d3cfd8b).

Here is how your development with hotreloading could look like:




https://github.com/ChillerDragon/ddnet_hotui/assets/20344300/85bc7a03-98a4-4fb1-b389-2cd2959a0911

