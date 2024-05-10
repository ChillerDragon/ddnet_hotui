#include <stdio.h>
#include <cstring>

#include "base/system.h"
#include "engine/keys.h"
#include "game/client/render.h"
#include "game/editor/editor.h"
#include "game/client/ui_rect.h"
#include "engine/graphics.h"
#include "game/generated/protocol7.h"

#include <game/client/gameclient.h>

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
	#include "scopes/editor_scope.h"

	MapView()->SetWorldOffset({32.0f * 10, 32.0f * 1});
}

// void1, size1, ...
// are set to the values you pass to HotVoidPtrs()
// if you do not pass values they will be null and 0
// you can pass any kind of variable by casting it to a void ptr and then
// casting it back to its type in here
void hot_void_ptrs(
	void *void1, size_t size1,
	void *void2, size_t size2,
	void *void3, size_t size3,
	void *void4, size_t size4,
	void *void5, size_t size5,
	void *void6, size_t size6)
{
	// CTeeRenderInfo *pInfo = (CTeeRenderInfo *)void1;
	// pInfo->m_Sixup.m_aColors[protocol7::SKINPART_BODY] = ColorRGBA(1,0,0,1);
}

}
