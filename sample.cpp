#include <stdio.h>
#include <cstring>

#include "../ddnet/src/game/editor/editor.h"
#include "../ddnet/src/game/client/ui_rect.h"
#include "../ddnet/src/engine/graphics.h"

extern "C"{

// View1, View2, ..
// are set to the values you pass to HotCuiRects()
// if you do not pass values it will be set to an empty new CUIRect
void hot_cui_rects(
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

// View1, View2, ..
// are set to the values you pass to EditorHotCuiRects()
// if you do not pass values it will be set to an empty new CUIRect
// pEditor might be a nullptr
void editor_hot_cui_rects(
	CEditor *pEditor,
	CUIRect &View1,
	CUIRect &View2,
	CUIRect &View3,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6)
{
	pEditor->MapView()->SetWorldOffset({32.0f * 10, 32.0f * 1});
}

}
