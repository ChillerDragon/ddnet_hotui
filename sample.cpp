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

	float MouseX = pEditor->m_RawMouseX;
	float MouseY = pEditor->m_RawMouseY;

	dbg_msg("chiller", "---------------------------");

	for(size_t g = 0; g < m_Map.m_vpGroups.size(); g++)
	{
		const std::shared_ptr<CLayerGroup> pGroup = m_Map.m_vpGroups[g];
		for(size_t l = 0; l < pGroup->m_vpLayers.size(); l++)
		{
			const std::shared_ptr<CLayer> pLayer = pGroup->m_vpLayers[l];
			int LayerType = pLayer->m_Type;
			if(LayerType != LAYERTYPE_TILES &&
				LayerType != LAYERTYPE_FRONT &&
				LayerType != LAYERTYPE_TELE &&
				LayerType != LAYERTYPE_SPEEDUP &&
				LayerType != LAYERTYPE_SWITCH &&
				LayerType != LAYERTYPE_TUNE)
				continue;
			if(pLayer != m_Map.m_pGameLayer)
				continue;

			std::shared_ptr<CLayerTiles> pTiles = std::static_pointer_cast<CLayerTiles>(pLayer);
			// pGroup->MapScreen();

			CUIRect Rect;
			Rect.x = UI()->MouseWorldX();
			Rect.y = UI()->MouseWorldY();
			Rect.w = 0;
			Rect.h = 0;

			RECTi r;
			pTiles->Convert(Rect, &r);
			pTiles->Clamp(&r);

			dbg_msg("chiller", "x=%.2f", UI()->MouseWorldX());
			dbg_msg("chiller", "r.x=%d", r.x);

			// UI()->MapScreen();

			// float aMapping[4];
			// pGroup->Mapping(aMapping);
			// int x = aMapping[0] + (aMapping[2] - aMapping[0]) / 2;
			// int y = aMapping[1] + (aMapping[3] - aMapping[1]) / 2;
			// dbg_msg("chiller", "x=%d", x / 32);
			// x += MouseX - (MapView()->GetWorldOffset().x * pGroup->m_ParallaxX / 100) - pGroup->m_OffsetX;
			// y += MouseY - (MapView()->GetWorldOffset().y * pGroup->m_ParallaxY / 100) - pGroup->m_OffsetY;
			// dbg_msg("chiller", "UI()->MouseWorldY()=%.2f - (%.2f * %.2f) - %d ==> %d / 32 ==> %d", MouseY, MapView()->GetWorldOffset().y, pGroup->m_ParallaxY / 100.0f, pGroup->m_OffsetY, y, y / 32);
			// x /= 32;
			// y /= 32;

			// dbg_msg("chiller", "x=%d y=%d g=%zu l=%zu", x, y, g, l);

			// if(x < 0 || x >= pTiles->m_Width)
			// 	continue;
			// if(y < 0 || y >= pTiles->m_Height)
			// 	continue;
			// CTile Tile = pTiles->GetTile(x, y);

			// if(Tile.m_Index)
			// {
			// 	dbg_msg("chiller", "tile=%d", Tile.m_Index);
			// }
		}
	}
}

}
