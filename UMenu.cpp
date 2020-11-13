#include "UMenu.h"
#include "UDialog.h"

BOOL UMenuItem::Set(MENUITEMTYPE type, STRING text, VOID* data)
{
	m_type = type;
	m_text = text;
	m_data = data;
	return TRUE;
}

BOOL UMenuItem::Create(UMenu* parent)
{
	m_parent = parent;
	return TRUE;
}

BOOL UMenuItem::Disable()
{
	m_show = UMS_DISABLE;
	return TRUE;
}

BOOL UMenuItem::Formal()
{
	m_show = UMS_FORMAL;
	return TRUE;
}

MENUITEMTYPE UMenuItem::GetType()
{
	return m_type;
}

BOOL UMenuItem::SetShowMode(UMENUSTATE mode)
{
	m_show = mode;
	return TRUE;
}

UMENUSTATE UMenuItem::GetShowMode()
{
	return m_show;
}

BOOL UMenuItem::SetText(STRING text)
{
	m_text = text;
	return m_parent->ResetWidth();
}

STRING UMenuItem::GetText()
{
	return m_text;
}

BOOL UMenuItem::SetData(VOID* data)
{
	m_data=data;
	return TRUE;
}

VOID* UMenuItem::GetData()
{
	return m_data;
}

BOOL UMenuItem::SetBitmap(HBITMAP bmp)
{
	if (m_type == MIT_TEXT) {
		m_data = bmp;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

HBITMAP UMenuItem::GetBitmap()
{
	if (m_type == MIT_TEXT) {
		return (HBITMAP)m_data;
	}
	else {
		return nullptr;
	}
}

BOOL UMenuItem::Check()
{
	if (m_type == MIT_CHECK) {
		m_data = (VOID*)(!((BOOL)m_data));
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL UMenuItem::SetCheck(BOOL bChecked)
{
	if (m_type == MIT_CHECK) {
		m_data = (VOID*)bChecked;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL UMenuItem::GetCheck()
{
	if (m_type == MIT_CHECK) {
		return (BOOL)m_data;
	}
	else {
		return FALSE;
	}
}

UINT UMenuItem::GetWidth()
{
	UINT width = wnd.charWidth * m_text.length() + MI_ICON_WIDTH+MI_PULL_WIDTH;
	return width;
}

UINT UMenuItem::GetHeight()
{
	switch (m_type) {
	case MIT_LINE:
		return MI_L_HEIGHT;
	default:
		return MI_O_HEIGHT;
	}
}

UINT UMenu::GetID()
{
	return m_id;
}

BOOL UMenu::SetWidth(UINT width)
{
	m_width = width;
	return TRUE;
}

UINT UMenu::GetWidth()
{
	return m_width;
}

UMenu* UMenu::GetParent()
{
	return m_parent;
}

UMenuItem* UMenu::GetChild(UINT n)
{
	return &m_pItems[n];
}

UINT UMenu::AddItem(UMenuItem* item)
{
	m_width = max(m_width, item->GetWidth());
	m_pItems[m_nItems]=*item;
	return m_nItems++;
}

UINT UMenu::AddItem(MENUITEMTYPE type, STRING text, VOID* data)
{
	m_pItems[m_nItems].Set(MIT_TEXT, text, data);
	m_width = max(m_width, m_pItems[m_nItems].GetWidth());
	return m_nItems++;
}

UINT UMenu::AddLine()
{
	UMenuItem item(MIT_LINE);
	m_width = max(m_width, item.GetWidth());
	m_pItems[m_nItems]=item;
	return m_nItems++;
}

UINT UMenu::AddText(STRING text, HBITMAP bmp)
{
	return AddItem(MIT_TEXT, text, bmp);
}

UINT UMenu::AddCheck(STRING text, BOOL bChecked)
{
	return AddItem(MIT_CHECK, text, (VOID*)bChecked);
}

UINT UMenu::AddPull(STRING text, UMenu* menu)
{
	return AddItem(MIT_PULL, text, menu);
}

BOOL UMenu::ResetWidth()
{
	m_width = MI_MENU_WIDTH;
	for (UINT i = 0; i < m_nItems; i++) {
		m_width = max(m_width, m_pItems[i].GetWidth());
	}
	return TRUE;
}

BOOL UMenu::Create(UDialog* dlg, POINT* p)
{
	m_dlg = dlg;
	m_p = *p;
	for (UINT i = 0; i < m_nItems; i++) {
		m_pItems[i].Create(this);
	}
	m_dlg->SetMenu(this);
	return TRUE;
}

BOOL UMenu::Show()
{/*
	UINT y=m_p.y;
	for (UINT i = 0; i < m_nItems; i++) {
		y += m_pItems[i].GetHeight();
	}
	URect rcmenu(m_p.x, m_p.y, m_width, y - m_p.y);
	DrawRect(&rcmenu, CR_M_FORMAL);
	y = m_p.y;
	for (UINT i = 0; i < m_nItems; i++) {
		UINT h = m_pItems[i].GetHeight();
		URect rc(rcmenu.l + MI_LSPACE , y, m_width - MI_LSPACE - MI_RSPACE ,h);
		URect rctext(rc.l + MI_ICON_WIDTH, y, m_width - MI_ICON_WIDTH - MI_PULL_WIDTH, h);
		y += h;
		URect rctmp;
		switch (m_pItems[i].GetShowMode()) {
		case UMS_FOCUS:
			switch (m_pItems[i].GetType()) {
			case MIT_LINE:
				rctmp.set(rc.l + MI_ICON_WIDTH, rc.t + rc.h / 2, rc.w - MI_ICON_WIDTH - MI_LINE_RSPACE, 0);
				DrawLine(&rctmp, CL_M_FORMAL, 1);
				break;
			case MIT_NULL:
				break;
			case MIT_TEXT:
				DrawRect(&rc, CR_MI_FOCUS);
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				rctmp.set(rc.l + MI_ICON_LSPACE, rc.t + MI_ICON_TSPACE, MI_ICON_WIDTH - MI_ICON_RSPACE, h - MI_ICON_TSPACE - MI_ICON_BSPACE);
				DrawBitmap(&rctmp, m_pItems[i].GetBitmap());
				break;
			case MIT_CHECK:
				DrawRect(&rc, CR_MI_FOCUS);
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				rctmp.set(rc.l + MI_ICON_LSPACE, rc.t + MI_ICON_TSPACE, MI_ICON_WIDTH - MI_ICON_RSPACE, h - MI_ICON_TSPACE - MI_ICON_BSPACE);
				if (m_pItems[i].GetCheck()) {
					DrawStringNoborderRect(&rctmp, "√", CB_M_C_FORMAL, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
				}
				break;
			case MIT_PULL:
				DrawRect(&rc, CR_MI_FOCUS);
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				DrawNoborderTriangle(rc.r() - MI_PULL_WIDTH + MI_PULL_LSPACE, rc.t + MI_PULL_VSPACE, rc.r() - MI_PULL_WIDTH + MI_PULL_LSPACE, rc.b() - MI_PULL_VSPACE, rc.r() - MI_PULL_RSPACE, rc.t + rc.h / 2, CB_M_P_FORMAL);
				break;
			}
			break;
		case UMS_CLICK:
			break;
		case UMS_DISABLE:

			break;
		case UMS_FORMAL:
		default:
			switch (m_pItems[i].GetType()) {
			case MIT_LINE:
				rctmp.set(rc.l + MI_ICON_WIDTH, rc.t + rc.h / 2, rc.w - MI_ICON_WIDTH - MI_LINE_RSPACE, 0);
				DrawLine(&rctmp, CL_M_FORMAL, 1);
				break;
			case MIT_NULL:
				break;
			case MIT_TEXT:
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				rctmp.set(rc.l + MI_ICON_LSPACE, rc.t + MI_ICON_TSPACE, MI_ICON_WIDTH - MI_ICON_RSPACE, h - MI_ICON_TSPACE - MI_ICON_BSPACE);
				DrawBitmap(&rctmp, m_pItems[i].GetBitmap());
				break;
			case MIT_CHECK:
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				rctmp.set(rc.l + MI_ICON_LSPACE, rc.t + MI_ICON_TSPACE, MI_ICON_WIDTH - MI_ICON_RSPACE, h - MI_ICON_TSPACE - MI_ICON_BSPACE);
				if (m_pItems[i].GetCheck()) {
					DrawStringNoborderRect(&rctmp, "√", CB_M_C_FORMAL, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
				}
				break;
			case MIT_PULL:
				DrawString(&rctext, m_pItems[i].GetText(), CT_M_FORMAL, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
				DrawNoborderTriangle(rc.r() - MI_PULL_WIDTH + MI_PULL_LSPACE, rc.t + MI_PULL_VSPACE, rc.r() - MI_PULL_WIDTH + MI_PULL_LSPACE, rc.b() - MI_PULL_VSPACE, rc.r() - MI_PULL_RSPACE, rc.t + rc.h / 2, CB_M_P_FORMAL);
				break;
			}
			break;
		}
	}*/
	return TRUE;
}

BOOL UMenu::Disable()
{
	m_show = UMS_DISABLE;
	return TRUE;
}

BOOL UMenu::Formal()
{
	m_show = UMS_FORMAL;
	return TRUE;
}

BOOL UMenu::Close()
{
	m_dlg->SetMenu(nullptr);
	delete this;
	return TRUE;
}

//BOOL UMenu::isIn(POINT* p)
//{
//	UINT y = m_p.y;
//	for (UINT i = 0; i < m_nItems; i++) {
//		y += m_pItems[i].GetHeight();
//	}
//	URect rcmenu(m_p.x, m_p.y, m_width, y - m_p.y);
//	return rcmenu.PointInRect(p);
//}
//
//BOOL UMenu::OnMouse()
//{
//	if (m_show == UMS_DISABLE)return FALSE;
//	m_show = UMS_FOCUS;
//	UINT y = m_p.y;
//	for (UINT i = 0; i < m_nItems; i++) {
//		y += m_pItems[i].GetHeight();
//	}
//	URect rcmenu(m_p.x, m_p.y, m_width, y - m_p.y);
//	y = m_p.y;
//	for (UINT i = 0; i < m_nItems; i++) {
//		UINT h = m_pItems[i].GetHeight();
//		URect rc(rcmenu.l + MI_LSPACE, y, m_width - MI_LSPACE, h);
//		y += h;
//		if (rc.PointInRect(&p)) {
//			if (m_lastcall != -1) {
//				m_pItems[m_lastcall].SetShowMode(UMS_FORMAL);
//			}
//			if (m_pItems[i].GetShowMode() != UMS_DISABLE) {
//				m_pItems[i].SetShowMode(UMS_FOCUS);
//			}
//			m_lastcall = i;
//			continue;
//		}
//	}
//	return TRUE;
//}
//
//BOOL UMenu::OnMouseLeave()
//{
//	if (m_show == UMS_DISABLE)return FALSE;
//	m_show = UMS_FORMAL;
//	if (m_lastcall != -1) {
//		m_pItems[m_lastcall].SetShowMode(UMS_FORMAL);
//	}
//	return TRUE;
//}
//
//BOOL UMenu::OnDisable()
//{
//	m_show = UMS_DISABLE;
//	return TRUE;
//}
//
//BOOL UMenu::OnLClick()
//{
//	if (m_show == UMS_DISABLE)return FALSE;
//	m_show = UMS_CLICK;
//	return TRUE;
//}
//
//BOOL UMenu::OnRClick()
//{
//	if (m_show == UMS_DISABLE)return FALSE;
//	m_show = UMS_CLICK;
//	return TRUE;
//}

BOOL UMenu::OnTimer()
{
	return 0;
}

BOOL UMenu::OnMouseMove(POINT* p)
{
	return 0;
}

BOOL UMenu::OnLDown(POINT* p)
{
	return 0;
}

BOOL UMenu::OnLUp(POINT* p)
{
	return 0;
}

BOOL UMenu::OnLClick(POINT* p)
{
	return 0;
}

BOOL UMenu::OnRDown(POINT* p)
{
	return 0;
}

BOOL UMenu::OnRUp(POINT* p)
{
	return 0;
}

BOOL UMenu::OnRClick(POINT* p)
{
	return 0;
}

BOOL UMenu::OnKey(KEY_EVENT_RECORD* k)
{
	return 0;
}

BOOL UMenu::OnWhelled(POINT* p, UINT n)
{
	return 0;
}

BOOL UMenu::OnString(STRING* s)
{
	return 0;
}

BOOL UMenu::OnShow(UPaint* p)
{
	return 0;
}
