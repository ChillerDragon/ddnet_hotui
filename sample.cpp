#include <stdio.h>
#include <cstring>

#include "../ddnet/src/base/system.h"
#include "../ddnet/src/engine/keys.h"
#include "../ddnet/src/game/editor/editor.h"
#include "../ddnet/src/game/client/ui_rect.h"
#include "../ddnet/src/engine/graphics.h"
#include "engine/input.h"

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

const char *str_find_nocase_char(const char *haystack, char needle)
{
	while(*haystack)
	{
		if(tolower((unsigned char)*haystack) == tolower(needle))
			return haystack;
		haystack++;
	}

	return 0;
}

bool chiller_fuzzy_match(const char *pHaystack, const char *pNeedle)
{
	if(!pNeedle || !pNeedle[0])
		return false;
	const char *pHit = str_find_nocase_char(pHaystack, pNeedle[0]);
	printf("'== pHit=%s'\n", pHit);
	for(int i = 0; i < str_length(pNeedle); i++)
	{
		if(!pHit)
			return false;
		char search = pNeedle[i];
		pHit = str_find_nocase_char(pHit, search);
		printf("'%c' hit=%s\n", search, pHit);
	}
	printf("'-------------------'\n");
	return pHit;
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

	// printf("%s\n", str_find_nocase_char("add quad", 'a'));

	auto Ui = [pEditor]() -> CUi* { return pEditor->Ui(); };
	auto Input = [pEditor]() -> IInput* { return pEditor->Input(); };
	int m_Dialog = pEditor->m_Dialog;
	int &m_PromptSelectedIndex = pEditor->m_PromptSelectedIndex;
	std::vector<char *> &m_vpCompletePrompList = pEditor->m_vpCompletePrompList;
	std::vector<const char *> &m_vpFilteredPrompList = pEditor->m_vpFilteredPrompList;
	CLineInputBuffered<IO_MAX_PATH_LENGTH> &m_PromptInput = pEditor->m_PromptInput;

	m_vpCompletePrompList.clear();
	m_vpCompletePrompList.emplace_back((char *)"Add Quad");
	m_vpCompletePrompList.emplace_back((char *)"Add Sound");
	m_vpCompletePrompList.emplace_back((char *)"Add Group");
	m_vpCompletePrompList.emplace_back((char *)"Add tele layer");
	m_vpCompletePrompList.emplace_back((char *)"Add speedup layer");
	m_vpCompletePrompList.emplace_back((char *)"Add tune layer");
	m_vpCompletePrompList.emplace_back((char *)"Add front layer");
	m_vpCompletePrompList.emplace_back((char *)"Add switch layer");
	m_vpCompletePrompList.emplace_back((char *)"Add quads layer");
	m_vpCompletePrompList.emplace_back((char *)"Add tile layer");
	m_vpCompletePrompList.emplace_back((char *)"Add sound layer");
	m_vpCompletePrompList.emplace_back((char *)"Save As");
	m_vpCompletePrompList.emplace_back((char *)"Save Copy");
	m_vpCompletePrompList.emplace_back((char *)"Toggle High Detail");
	m_vpCompletePrompList.emplace_back((char *)"Refocus");
	m_vpCompletePrompList.emplace_back((char *)"Envelopes");
	m_vpCompletePrompList.emplace_back((char *)"Server settings");
	m_vpCompletePrompList.emplace_back((char *)"History");
	m_vpCompletePrompList.emplace_back((char *)"Toggle preview of how layers will be zoomed in-game");

	CUIRect Suggestions;

	View.HSplitMid(&Prompt, nullptr);

	Prompt.VSplitMid(nullptr, &PromptBox);

	Prompt.Draw(ColorRGBA(0, 0, 0, 0.75f), IGraphics::CORNER_ALL, 10.0f);
	Prompt.HSplitTop(32.0f, &PromptBox, &Suggestions);
	PromptBox.Draw(ColorRGBA(1, 0, 0, 0.75f), IGraphics::CORNER_ALL, 10.0f);

	if(Ui()->DoClearableEditBox(&m_PromptInput, &PromptBox, 10.0f))
	{
		m_PromptSelectedIndex = 0;
		m_vpFilteredPrompList.clear();
		for(const char *Item : m_vpCompletePrompList)
		{
			// if(m_PromptInput.IsEmpty() || str_find_nocase(Item, m_PromptInput.GetString()))
			if(m_PromptInput.IsEmpty() || chiller_fuzzy_match(Item, m_PromptInput.GetString()))
			{
				m_vpFilteredPrompList.push_back(Item);
			}
		}
	}
	Ui()->SetActiveItem(&m_PromptInput);

	s_ListBox.SetActive(m_Dialog == DIALOG_NONE && !Ui()->IsPopupOpen());
	s_ListBox.DoStart(15.0f, m_vpFilteredPrompList.size(), 1, 5, m_PromptSelectedIndex, &Suggestions, false);

	for(size_t i = 0; i < m_vpFilteredPrompList.size(); i++)
	{
		const CListboxItem Item = s_ListBox.DoNextItem(m_vpFilteredPrompList[i], m_PromptSelectedIndex >= 0 && (size_t)m_PromptSelectedIndex == i);
		if(!Item.m_Visible)
			continue;

		CUIRect Button, FileIcon, TimeModified;
		Item.m_Rect.VSplitLeft(Item.m_Rect.h, &FileIcon, &Button);
		Button.VSplitLeft(5.0f, nullptr, &Button);
		Button.VSplitRight(100.0f, &Button, &TimeModified);
		Button.VSplitRight(5.0f, &Button, nullptr);

		SLabelProperties Props;
		Props.m_MaxWidth = Button.w;
		Props.m_EllipsisAtEnd = true;
		Ui()->DoLabel(&Button, m_vpFilteredPrompList[i], 10.0f, TEXTALIGN_ML, Props);

	}

	const int NewSelected = s_ListBox.DoEnd();
	if(m_PromptSelectedIndex != NewSelected)
	{
		m_PromptSelectedIndex = NewSelected;


	}

	if(Ui()->ConsumeHotkey(CUi::HOTKEY_ENTER) || Input()->KeyIsPressed(KEY_RETURN))
	{
		dbg_msg("editor", "enter");
		if(m_PromptSelectedIndex > 0)
		{
			const char *pName = m_vpFilteredPrompList[m_PromptSelectedIndex];
			dbg_msg("editor", "selected %s", pName);
		}
	}
}

}
