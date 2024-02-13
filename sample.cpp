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

		float aPoints[4];
		pGroup->Mapping(aPoints);
		float TopLeftX = aPoints[0];
		float TopLeftY = aPoints[1];
		float BottomRightX = aPoints[2];
		float BottomRightY = aPoints[3];

		float WorldWidth = aPoints[2] - aPoints[0];
		float WorldHeight = aPoints[3] - aPoints[1];

		// int x = aPoints[0] + WorldWidth * ((HoverTile.m_X * 32) / Graphics()->WindowWidth());
		// int y = aPoints[1] + WorldHeight * ((HoverTile.m_Y * 32) / Graphics()->WindowHeight());
		// m_MouseDeltaWx = m_MouseDeltaX * (WorldWidth / Graphics()->WindowWidth());
		// m_MouseDeltaWy = m_MouseDeltaY * (WorldHeight / Graphics()->WindowHeight());

		float TileScale = 64 / pEditor->m_MouseWScale;
		int x = HoverTile.m_X * TileScale - MapView()->GetWorldOffset().x;
		int y = HoverTile.m_Y * TileScale - MapView()->GetWorldOffset().y;

		dbg_msg("c", "tile at %d %d", x, y);
		Graphics()->TextureClear();
		Graphics()->SetColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Graphics()->DrawRect(x, y, TileScale, TileScale, ColorRGBA(0.0f, 0.0f, 1.0f, 0.5f), IGraphics::CORNER_ALL, 3.0f);
	}
}

}
