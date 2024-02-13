auto UI = [pEditor]() -> CUI* { return pEditor->UI(); };
auto MapView = [pEditor]() -> CMapView * { return pEditor->MapView(); };
auto Graphics = [pEditor]() -> IGraphics * { return pEditor->Graphics(); };
int m_Dialog = pEditor->m_Dialog;
CEditorMap &m_Map = pEditor->m_Map;
