#include "UDialog.h"
#include "UItem.h"
#include "UMenu.h"
#include "UWindow.h"

//VOID UDialog::SetSize(USHORT width, USHORT height)
//{
//	if (m_pItemMap != nullptr) {
//		for (int i = 0; i < width; i++) {
//			if (m_pItemMap[i] != nullptr) {
//				delete[]m_pItemMap[i];
//			}
//		}
//		delete[]m_pItemMap;
//	}
//	m_width = width;
//	m_height = height;
//	try {
//		m_pItemMap = new INT * [width];
//		for (int i = 0; i < width; i++) {
//			m_pItemMap[i] = new INT[height];
//		}
//	}
//	catch (std::bad_alloc&) {
//		MessageBox(GetConsoleWindow(), "ÄÚ´æ²»×ã£¡", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
//	}
//}

UItem* UDialog::AddItem(UItem* pNewItem)
{
	UItem* tmp = m_firstItem;
	m_firstItem = pNewItem;
	return tmp;
}

BOOL UDialog::SetStatusText(STRING text)
{
	m_statusText = text;
	return DrawStatusBar();
}
STRING UDialog::GetStatusText()
{
	return m_statusText;
}
INPUT_RECORD UDialog::GetRecord()
{
	return m_rec;
}
BOOL UDialog::SetMenu(UMenu* menu)
{
	if (m_menu != nullptr && menu != nullptr) {
		;
		m_menu->Close();
	}
	m_menu = menu;
	return TRUE;
}
UItem* UDialog::SetKeyCall(UItem* pItem)
{
	UItem* tmp = m_keyCall;
	m_keyCall = pItem;
	return tmp;
}
BOOL UDialog::SetTarget(UItem* pItem)
{
	if (m_target != nullptr) {
		m_target->OnNoTarget();
	}
	m_target = pItem;
	return TRUE;
}

BOOL UDialog::Run()
{
	OnInitDialog();
	return wnd.BeginMsgLoop();
}

BOOL UDialog::End()
{
	if (m_menu != nullptr) {
		m_menu->Close();
	}
	if (wnd.GetDlg() == this) {
		wnd.EndMsgLoop();
	}
	return TRUE;
}


BOOL UDialog::DrawStatusBar()
{
	URect rc(0,m_rect.h - 20, m_rect.w, 20);
	return/* DrawStringNoborderRect(&rc, m_statusText, CR_STB_FORMAL, CT_STB_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX)*/TRUE;
}

BOOL UDialog::WaitTime()
{
	Sleep(MSG_TIME);
	return TRUE;
}

BOOL UDialog::OnTimer()
{
	return 0;
}

BOOL UDialog::OnCtrlMsg(DWORD CtrlType)
{
	return TRUE;
}

BOOL UDialog::OnMouseMove(POINT* p)
{
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		if (i->OnMouseMove(p)) {
			break;
		}
	}
	return TRUE;
}

BOOL UDialog::OnLDown(POINT* p)
{
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		if (i->OnLDown(p)) {
			m_lastLDown = i;
			m_lastRDown = nullptr;
			break;
		}
	}
	return TRUE;
}

BOOL UDialog::OnLUp(POINT* p)
{
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		if (i->OnLUp(p)) {
			if (i == m_lastLDown) {
				i->OnLClick(p);
			}
			m_lastLDown = nullptr;
			m_lastRDown = nullptr;
			break;
		}
	}
	return TRUE;
}

BOOL UDialog::OnLClick(POINT* p)
{
	return TRUE;
}

BOOL UDialog::OnRDown(POINT* p)
{
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		if (i->OnRDown(p)) {
			m_lastLDown = nullptr;
			m_lastRDown = i;
			break;
		}
	}
	return TRUE;
}

BOOL UDialog::OnRUp(POINT* p)
{
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		if (i->OnRUp(p)) {
			if (i == m_lastRDown) {
				i->OnRClick(p);
			}
			m_lastLDown = nullptr;
			m_lastRDown = nullptr;
			break;
		}
	}
	return TRUE;
}

BOOL UDialog::OnRClick(POINT* p)
{
	return TRUE;
}

BOOL UDialog::OnKey(KEY_EVENT_RECORD* k)
{
	return 0;
}

BOOL UDialog::OnWhelled(POINT* p,UINT n)
{
	return TRUE;
}

BOOL UDialog::OnString(STRING* s)
{
	return 0;
}

BOOL UDialog::OnShow(UPaint* p)
{
	UPaint paint;
	paint.Make(*p,m_rect.w,m_rect.h);
	BOOL bRet = TRUE;
	//Draw background
	paint.DrawNoborderRect(&m_rect, CB_WINDOW);
	for (UItem* i = m_firstItem; i != nullptr; i = i->GetNext()) {
		i->OnShow(&paint);
	}
	if (m_menu != nullptr) {
		m_menu->Show();
	}
	p->Bitblt(&m_rect, paint);
	paint.Delete();
	return bRet;
}

BOOL UDialog::OnInitDialog()
{
	return TRUE;
}


