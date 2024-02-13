#include <stdio.h>
#include <cstring>

#include "../ddnet/src/engine/keys.h"
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


// TODO: use CLayerTiles somehow
int ConvertX(float x) { return (int)(x / 32.0f); }
int ConvertY(float y) { return (int)(y / 32.0f); }

void Convert(CUIRect Rect, RECTi *pOut)
{
	pOut->x = ConvertX(Rect.x);
	pOut->y = ConvertY(Rect.y);
	pOut->w = ConvertX(Rect.x + Rect.w + 31) - pOut->x;
	pOut->h = ConvertY(Rect.y + Rect.h + 31) - pOut->y;
}

void Snap(CUIRect *pRect)
{
	RECTi Out;
	Convert(*pRect, &Out);
	pRect->x = Out.x * 32.0f;
	pRect->y = Out.y * 32.0f;
	pRect->w = Out.w * 32.0f;
	pRect->h = Out.h * 32.0f;
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

	std::vector<CLayerSelector::CHoverTile> &m_vHoverTiles = pEditor->LayerSelector()->m_vHoverTiles;

	for(auto HoverTile : m_vHoverTiles)
	{
		const std::shared_ptr<CLayerGroup> pGroup = m_Map.m_vpGroups[HoverTile.m_Group];
		const std::shared_ptr<CLayer> pLayer = pGroup->m_vpLayers[HoverTile.m_Layer];
		auto pLayerTiles = std::static_pointer_cast<CLayerTiles>(pLayer);

		float wx = UI()->MouseWorldX();
		float wy = UI()->MouseWorldY();

		pGroup->MapScreen();

		CUIRect Rect;
		Rect.x = wx;
		Rect.y = wy;
		Rect.w = 0;
		Rect.h = 0;

		Graphics()->TextureClear();
		Graphics()->QuadsBegin();
		Graphics()->SetColor(0.0f, 1.0f, 0.0f, 0.5f);
		pLayerTiles->Snap(&Rect);
		IGraphics::CQuadItem QuadItem(Rect.x, Rect.y, Rect.w, Rect.h);
		Graphics()->QuadsDrawTL(&QuadItem, 1);
		Graphics()->QuadsEnd();

		UI()->MapScreen();
	}
}

}
