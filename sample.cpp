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

class CUI;

// View1, View2, ..
// are set to the values you pass to EditorHotCuiRects()
// if you do not pass values it will be set to an empty new CUIRect
// pEditor might be a nullptr
void editor_hot_cui_rects(
	CEditor *pEditor,
	CUIRect &View,
	CUIRect &Prompt,
	CUIRect &PromptBox,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6)
{
}

// View1, View2, ..
// are set to the values you pass to EditorHotCuiRects()
// if you do not pass values it will be set to an empty new CUIRect
// pEditor might be a nullptr
void editor_list_hot_cui_rects(
	CEditor *pEditor,
	CListBox &s_ListBox,
	CUIRect &View,
	CUIRect &Prompt,
	CUIRect &PromptBox,
	CUIRect &View4,
	CUIRect &View5,
	CUIRect &View6)
{
	auto UI = [pEditor]() -> CUI* { return pEditor->UI(); };


	View.HSplitMid(&Prompt, nullptr);

	Prompt.VSplitMid(nullptr, &PromptBox);

	Prompt.Draw(ColorRGBA(0, 0, 0, 0.75f), IGraphics::CORNER_ALL, 10.0f);
	Prompt.HSplitTop(32.0f, &PromptBox, nullptr);
	PromptBox.Draw(ColorRGBA(1, 0, 0, 0.75f), IGraphics::CORNER_ALL, 10.0f);

	UI()->DoLabel(&Prompt, "Search:", 10.0f, TEXTALIGN_ML);

	if(UI()->DoClearableEditBox(&pEditor->m_PromptInput, &PromptBox, 10.0f))
	{

	}

	int m_FilesSelectedIndex = 0;

	s_ListBox.DoStart(15.0f, pEditor->m_vpFilteredPrompList.size(), 1, 5, m_FilesSelectedIndex, &View, false);

}

}
