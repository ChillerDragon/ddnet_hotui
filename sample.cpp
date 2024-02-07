#include <stdio.h>
#include <cstring>

#include "../ddnet/src/game/client/ui_rect.h"
#include "../ddnet/src/engine/graphics.h"

extern "C"{

// View1, View2, ..
// are set to the values you pass to HotUi()
// if you do not pass values it will be set to an empty new CUIRect
void ui_tick(
	CUIRect &View1,
	CUIRect &View2,
	CUIRect &View3,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6)
{
	CUIRect Left, Right;
	View1.VSplitMid(&Left, &Right, 5.0f);

	Left.Draw(ColorRGBA(1, 1, 1, 0.25f), IGraphics::CORNER_ALL, 10.0f);
	// Right.Draw(ColorRGBA(1, 1, 1, 0.25f), IGraphics::CORNER_ALL, 10.0f);
}

}
