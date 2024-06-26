# ddnet_hotui
Iterate in ddnet ui development without rebooting the client. CUIRect hot reloading.

## how it looks like when it works

A old less fancy sample implementation can be seen [here](https://github.com/ChillerDragon/ddnet/commit/95695caadde37c4201c01c5c8d08f2068d3cfd8b).

Here is how your development with hot reloading could look like:

https://github.com/ChillerDragon/ddnet_hotui/assets/20344300/85bc7a03-98a4-4fb1-b389-2cd2959a0911

![output](https://github.com/ChillerDragon/ddnet_hotui/assets/20344300/512b3728-570a-4ee6-b279-68cbe5208b2b)

https://github.com/ChillerDragon/ddnet_hotui/assets/20344300/c3bebe56-374d-4fb6-aa89-87f26d927d23

![ddnet_hotui_ingame.gif](https://raw.githubusercontent.com/ChillerDragon/cdn/master/ddnet_hotui_ingame.gif)

## full on video tutorial on how to use it

[![ddnet hotui video tutorial](https://img.youtube.com/vi/S4Jwy62oRy8/hqdefault.jpg)](https://www.youtube.com/watch?v=S4Jwy62oRy8)

## folder setup

The examples assume you have the following setup.
```bash
git clone git@github.com:ChillerDragon/ddnet_hotui.git
git clone git@github.com:ddnet/ddnet.git --recursive
```

So a folder called ddnet/ with the ddnet source code.
And a folder with this repo right next to it. It further more expects you to run the client from ddnet/build/DDNet

So in the end it should look like this (simplified)
```
.
├── ddnet
│   ├── build
│   │   └── DDNet
│   └── src
└── ddnet_hotui
    ├── Makefile
    └── sample.cpp
```

If you nest it differently or named things differently. You have to adjust the paths in the sample.


## how to link up the code

Add this to the top of your ddnet client code C++ file
```C++
#include "../../ddnet_hotui/loader.h"
```

And this in the method where you want to do hot reloading
```C++
// void CMenus::RenderSettings(CUIRect MainView)
// {
	HotCuiRects(MainView);
// }
```

Also when compiling ddnet you need to make sure the ``-rdynamic`` flag is set.
So somewhere in your CMakeLists.txt add this line
```cmake
add_cxx_compiler_flag_if_supported(OUR_FLAGS_LINK -rdynamic)
```
or alternatively you can run this ``cmake .. -DCMAKE_CXX_FLAGS=-rdynamic``

Then you can play around in the ``sample.cpp`` file and run ``make`` when you are done. If the path [here](https://github.com/ChillerDragon/ddnet_hotui/blob/2e501b9e95dcb9a6d380a90f9a301d368cb42188/loader.h#L11)https://github.com/ChillerDragon/ddnet_hotui/blob/2e501b9e95dcb9a6d380a90f9a301d368cb42188/loader.h#L11 is correct you should see instant ui changes in your running client.

## traps

Do not use ``static`` variables in your hot reloaded code.
They will be confusing to debug. They will be reset to their initial value on every hot reload.
