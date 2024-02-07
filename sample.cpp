#include <stdio.h>
#include <cstring>

#include "../ddnet/src/game/client/ui_rect.h"
#include "../ddnet/src/engine/graphics.h"

extern "C"{

void ui_tick(CUIRect &View)
{
 	CUIRect Left, Right;
	View.VSplitMid(&Left, &Right, 5.0f);

	// Left.Draw(ColorRGBA(1, 1, 1, 0.25f), IGraphics::CORNER_ALL, 10.0f);
	Right.Draw(ColorRGBA(1, 1, 1, 0.25f), IGraphics::CORNER_ALL, 10.0f);
}
}
