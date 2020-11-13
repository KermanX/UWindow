#include "UItem.h"
#include "UDialog.h"




BOOL UItem::Create(UDialog* pDialog, URect* rc)
{
	m_pDialog = pDialog;
	m_next = pDialog->AddItem(this);
	m_rect = *rc;
	return TRUE;
}

BOOL UItem::SetKeyCall()
{
	m_keyCall = m_pDialog->SetKeyCall(this);
	return TRUE;
}

BOOL UItem::SetTarget()
{
	m_state.Target();
	return m_pDialog->SetTarget(this);
}

BOOL UItem::IsIn(POINT* p)
{
	return m_rect.PointInRect(p);
}

BOOL UItem::OnTimer()
{
	if (m_next != nullptr) {
		m_next->OnTimer();
	}
	return TRUE;
}

BOOL UItem::OnMouseMove(POINT* p)
{
	if (IsIn(p)) {
		m_state.Focus();
		return TRUE;
	}
	else {
		m_state.Formal();
	}
	return TRUE;
}

BOOL UItem::OnLDown(POINT* p)
{
	if (IsIn(p)) {
		m_state.Click();
		return TRUE;
	}
	return FALSE;
}

BOOL UItem::OnLUp(POINT* p)
{
	if (IsIn(p)) {
		m_state.Formal();
		return TRUE;
	}
	return FALSE;
}

BOOL UItem::OnLClick(POINT* p)
{
	return TRUE;
}

BOOL UItem::OnRDown(POINT* p)
{
	if (IsIn(p)) {
		m_state.Click();
		return TRUE;
	}
	return FALSE;
}

BOOL UItem::OnRUp(POINT* p)
{
	if (IsIn(p)) {
		m_state.Formal();
		return TRUE;
	}
	return FALSE;
}

BOOL UItem::OnRClick(POINT* p)
{
	return TRUE;
}

BOOL UItem::OnKey(KEY_EVENT_RECORD* k)
{
	if (m_keyCall != nullptr) {
		m_keyCall->OnKey(k);
	}
	return TRUE;
}

BOOL UItem::OnWhelled(POINT* p, UINT n)
{
	if (m_next != nullptr) {
		m_next->OnWhelled(p, n);
	}
	if (IsIn(p)) {
		return TRUE;
	}
	return FALSE;
}

BOOL UItem::OnString(STRING* s)
{
	if (m_next != nullptr) {
		m_next->OnString(s);
	}
	return FALSE;
}

BOOL UItem::OnShow(UPaint* p)
{
	return TRUE;
}

BOOL UItem::OnNoTarget()
{
	m_state.NoTarget();
	return TRUE;
}


BOOL UButton::SetText(STRING text)
{
	m_text = text;
	return TRUE;
}

STRING UButton::GetText()
{
	return m_text;
}

BOOL UButton::Create(UDialog* pDialog, URect* rc, STRING text, DLGMSGFUNC onLClick, DLGMSGFUNC onRClick)
{
	m_text = text;
	m_onLClick = onLClick;
	m_onRClick = onRClick;
	return UItem::Create(pDialog, rc);
}

BOOL UButton::OnTimer()
{
	m_dState += m_dDelta;
	if (m_dState < 0) m_dState = 0;
	if (m_dState > 100) m_dState = 100;
	return TRUE;
}

BOOL UButton::OnMouseMove(POINT* p)
{
	if (UItem::OnMouseMove(p)) {
		m_dDelta = -15;
		return TRUE;
	}
	m_dDelta = 0;
	return FALSE;
}

BOOL UButton::OnLDown(POINT* p)
{
	if (UItem::OnLDown(p)) {
		m_dDelta = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnLUp(POINT* p)
{
	if (UItem::OnLUp(p)) {
		m_dDelta = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnLClick(POINT* p)
{
	if (UItem::OnLClick(p)) {
		if (m_onLClick != nullptr) {
			m_onLClick(m_parent, this);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnRDown(POINT* p)
{
	if (UItem::OnRDown(p)) {
		m_dDelta = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnRUp(POINT* p)
{
	if (UItem::OnRUp(p)) {
		m_dDelta = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnRClick(POINT* p)
{
	if (UItem::OnRClick(p)) {
		if (m_onRClick != nullptr) {
			m_onRClick(m_parent, this);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL UButton::OnShow(UPaint* p)
{
	if (UItem::OnShow(p) == FALSE) {
		return FALSE;
	}
	switch (m_state.GetState()) {
	case UWS_HIDE:
		break;
	case UWS_DISABLE:
		p->DrawRect(&m_rect, CR_BTN_DISABLE);
		p->DrawString(&m_rect, m_text, CT_BTN_DISABLE);
		break;
	default:
		switch (m_state.GetShow()) {
		case UWS_FOCUS:
			p->DrawRect(&m_rect, CR_BTN_FOCUS);
			p->DrawString(&m_rect, m_text, CT_BTN_FORMAL);
			break;
		case UWS_CLICK:
			p->DrawRect(&m_rect, CR_BTN_CLICK);
			p->DrawString(&m_rect, m_text, CT_BTN_FORMAL);
			break;
		default:
			p->DrawRect(&m_rect, CR_BTN_FORMAL);
			p->DrawString(&m_rect, m_text, CT_BTN_FORMAL);
			break;
		}
		break;
	}
	return TRUE;
}

//
//BOOL UCheckBox::SetCheck(BOOL isCheck)
//{
//	BOOL bRet = m_isCheck;
//	m_isCheck = isCheck;
//	return bRet;
//}
//
//BOOL UCheckBox::GetCheck()
//{
//	return m_isCheck;
//}
//
//BOOL UCheckBox::GetCheckRect(URect* rc)
//{
//	rc->l = m_rect.l;
//	rc->t = m_rect.t;
//	rc->w = 16;
//	rc->h = 16;
//	return TRUE;
//}
//
//BOOL UCheckBox::GetTextRect(URect* rc)
//{
//	rc->l = m_rect.l + 21;
//	rc->t = m_rect.t;
//	rc->w = m_rect.w - 21;
//	rc->h = 16;
//	return TRUE;
//}
//
//BOOL UCheckBox::Create(UDialog* pDialog, URect* rc, STRING text, DLGMSGFUNC onLClick, BOOL isCheck)
//{
//	m_text = text;
//	m_onLClick = onLClick;
//	m_isCheck = isCheck;
//	return UItem::Create(pDialog, rc);
//}
//
//BOOL UCheckBox::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	URect rcText;
//	GetTextRect(&rcText);
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		DrawCheckRect(CR_CHB_FOCUS);
//		DrawStringNoborderRect(&m_rect, m_text, CT_CHB_FORMAL, CB_WINDOW, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//		break;
//	case UWS_CLICK:
//		DrawCheckRect(CR_CHB_CLICK);
//		DrawStringNoborderRect(&m_rect, m_text, CT_CHB_FORMAL, CB_WINDOW, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//		break;
//	case UWS_DISABLE:
//		DrawCheckRect(CR_CHB_DISABLE);
//		DrawStringNoborderRect(&m_rect, m_text, CT_CHB_DISABLE, CB_WINDOW, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//		break;
//	case UWS_FORMAL:
//	default:
//		DrawCheckRect(CR_CHB_FORMAL);
//		DrawStringNoborderRect(&m_rect, m_text, CT_CHB_FORMAL, CB_WINDOW, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UCheckBox::Check()
//{
//	m_isCheck = !m_isCheck;
//	return Show();
//}
//
//BOOL UCheckBox::DrawCheckRect(COLORREF pen, COLORREF brush)
//{
//	URect rc;
//	BOOL bRet = TRUE;
//	bRet &= GetCheckRect(&rc);
//	bRet &= DrawRect(&rc, pen, brush);
//	if (m_isCheck)bRet &= DrawString(&rc, "¡Ì", pen);
//	return bRet;
//}
//
//BOOL UCheckBox::OnLClick()
//{
//	if(UItem::OnLClick() ){
//		Check();
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL UStaticText::SetText(STRING text)
//{
//	m_text = text;
//	return TRUE;
//}
//
//STRING UStaticText::GetText()
//{
//	return m_text;
//}
//
//BOOL UStaticText::SetMode(BOOL isTransparent, COLORREF color, BOOL edge, UINT format)
//{
//	m_isTransparent = isTransparent;
//	m_color = color;
//	m_edge = edge;
//	m_format = format;
//	return TRUE;
//}
//
//BOOL UStaticText::GetMode(BOOL* isTransparent, COLORREF* color, BOOL* edge, UINT* format)
//{
//	if (isTransparent)*isTransparent = m_isTransparent;
//	if (color)*color = m_color;
//	if (edge)*edge = m_edge;
//	if (format)*format = m_format;
//	return TRUE;
//}
//
//BOOL UStaticText::ShowString()
//{
//	if (m_isTransparent) {
//		return DrawString(&m_rect, m_text, m_color, m_format);
//	}
//	else {
//		return DrawStringNoborderRect(&m_rect, m_text, m_color, CB_WINDOW, m_format);
//	}
//}
//
//BOOL UStaticText::Create(UDialog* pDialog, URect* rc, STRING text, BOOL edge, BOOL isTransparent, COLORREF color, UINT format)
//{
//	m_text = text;
//	m_isTransparent = isTransparent;
//	m_color = color;
//	m_edge = edge;
//	m_format = format;
//	return UItem::Create(pDialog, rc);
//}
//
//BOOL UStaticText::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FORMAL:
//	default:
//		BOOL bRet = TRUE;
//		if (m_edge) {
//			bRet &= DrawTransparentRect(&m_rect, RGB(0, 0, 0));
//		}
//		bRet &= ShowString();
//		return bRet;
//	}
//	return TRUE;
//}
//
//BOOL UProgressBar::SetPos(UINT pos)
//{
//	if (pos <= m_range) {
//		m_pos = pos;
//	}
//	else {
//		m_pos = 100;
//	}
//	return Show();
//}
//
//UINT UProgressBar::GetPos()
//{
//	return m_pos;
//}
//
//BOOL UProgressBar::SetPercent(long double percent)
//{
//	if (0 <= percent && percent <= 1) {
//		m_pos = (INT)((long double)percent * m_range);
//	}
//	else {
//		m_pos = m_range;
//	}
//	return Show();
//}
//
//long double UProgressBar::GetPersent()
//{
//	return (long double)(m_pos) / m_range;
//}
//
//BOOL UProgressBar::SetRange(UINT range)
//{
//	m_pos = (UINT)((long double)(range) * (long double)(m_pos) / (long double)(m_range));
//	m_range = range;
//	return TRUE;
//}
//
//UINT UProgressBar::GetRange()
//{
//	return m_range;
//}
//
//BOOL UProgressBar::SetStep(UINT rangeOfAStep)
//{
//	m_step = rangeOfAStep;
//	return TRUE;
//}
//
//UINT UProgressBar::GetStep()
//{
//	return m_step;
//}
//
//
//BOOL UProgressBar::Error(BOOL isError)
//{
//	URect rcBar;
//	GetBarRect(&rcBar);
//	if (isError) {
//		m_show = UWS_ERROR;
//		if (m_show == UWS_HIDE)return TRUE;
//		DrawRect(&m_rect, CR_PB_ERROR);
//		DrawRect(&rcBar, CB_PB_ERROR);
//	}
//	else {
//		m_show = UWS_FORMAL;
//		if (m_show == UWS_HIDE)return TRUE;
//		DrawRect(&m_rect, CR_PB_FORMAL);
//		DrawRect(&rcBar, CB_PB_FORMAL);
//	}
//	return TRUE;
//}
//
//BOOL UProgressBar::Pause(BOOL isPause)
//{
//	URect rcBar;
//	GetBarRect(&rcBar);
//	if (isPause) {
//		m_show = UWS_PAUSE;
//		if (m_show == UWS_HIDE)return TRUE;
//		DrawRect(&m_rect, CR_PB_PAUSE);
//		DrawRect(&rcBar, CB_PB_PAUSE);
//	}
//	else {
//		m_show = UWS_FORMAL;
//		if (m_show == UWS_HIDE)return TRUE;
//		DrawRect(&m_rect, CR_PB_FORMAL);
//		DrawRect(&rcBar, CB_PB_FORMAL);
//	}
//	return TRUE;
//}
//
//BOOL UProgressBar::GetBarRect(URect* rcBar)
//{
//	rcBar->l = m_rect.l;
//	rcBar->t = m_rect.t;
//	rcBar->w = (LONG)((long double)(m_rect.w) * (long double)(m_pos) / (long double)(m_range));
//	rcBar->h = m_rect.h;
//	return TRUE;
//}
//
//BOOL UProgressBar::Create(UDialog* pDialog, URect* rc, UINT range, UINT step)
//{
//	m_range = range;
//	m_step = step;
//	return UItem::Create(pDialog, rc);
//}
//
//BOOL UProgressBar::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	URect rcBar;
//	GetBarRect(&rcBar);
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		DrawRect(&m_rect, CR_PB_FOCUS);
//		DrawRect(&rcBar, CB_PB_FOCUS);
//		break;
//	case UWS_DISABLE:
//		DrawRect(&m_rect, CR_PB_DISABLE);
//		DrawRect(&rcBar, CB_PB_DISABLE);
//		break;
//	case UWS_ERROR:
//		DrawRect(&m_rect, CR_PB_ERROR);
//		DrawRect(&rcBar, CB_PB_ERROR);
//		break;
//	case UWS_PAUSE:
//		DrawRect(&m_rect, CR_PB_PAUSE);
//		DrawRect(&rcBar, CB_PB_PAUSE);
//		break;
//	case UWS_FORMAL:
//	default:
//		DrawRect(&m_rect, CR_PB_FORMAL);
//		DrawRect(&rcBar, CB_PB_FORMAL);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UProgressBar::Step()
//{
//	m_pos += m_step;
//	if (m_pos > m_range) {
//		m_pos = m_range;
//	}
//	return Show();
//}
//
//BOOL UStaticLine::Create(UDialog* pDialog, URect* rc, INT lineWidth)
//{
//	m_lineWidth = lineWidth;
//	return UItem::Create(pDialog, rc);
//}
//
//
//BOOL UStaticLine::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_DISABLE:
//		DrawLine(&m_rect, CL_LINE_DISABLE, m_lineWidth);
//		break;
//	case UWS_FORMAL:
//	default:
//		DrawLine(&m_rect, CL_LINE_FORMAL, m_lineWidth);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UStaticRect::Create(UDialog* pDialog, URect* rc, INT edgeWidth, DLGMSGFUNC onLClick, DLGMSGFUNC onRClick)
//{
//	m_edgeWidth = edgeWidth;
//	m_onLClick = onLClick;
//	m_onRClick = onRClick;
//	return UItem::Create(pDialog, rc);
//}
//
//
//BOOL UStaticRect::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		DrawRect(&m_rect, CR_RECT_FOCUS);
//		break;
//	case UWS_DISABLE:
//		DrawRect(&m_rect, CR_RECT_DISABLE);
//		break;
//	case UWS_FORMAL:
//	default:
//		DrawRect(&m_rect, CR_RECT_FORMAL);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UStaticRect::OnLClick()
//{
//	UItem::OnLClick();
//	if (m_onLClick != nullptr) {
//		m_onLClick(m_pDialog, this);
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL UStaticRect::OnRClick()
//{
//	if (UItem::OnRClick()) {
//		if (m_onRClick != nullptr) {
//			m_onRClick(m_pDialog, this);
//		}
//		return TRUE;
//	}
//	return FALSE;
//}
//
//
//
//BOOL UListBox::Add(STRING text)
//{
//	m_data.push_back(text);
//	return TRUE;
//}
//
//BOOL UListBox::Delete(INT nIndex)
//{
//	m_data.erase(m_data.begin() + nIndex);
//	return TRUE;
//}
//
//INT UListBox::Insert(INT nIndex, STRING text)
//{
//	m_data.insert(m_data.begin() + nIndex, text);
//	return TRUE;
//}
//
//BOOL UListBox::Empty()
//{
//	m_data.clear();
//	return TRUE;
//}
//
//BOOL UListBox::SetString(INT nIndex, STRING text)
//{
//	m_data[nIndex] = text;
//	return TRUE;
//}
//
//STRING UListBox::GetString(INT nIndex)
//{
//	return m_data[nIndex];
//}
//
//INT UListBox::Find(STRING text, INT nStart)
//{
//	std::vector<STRING>::iterator it = std::find(m_data.begin() + nStart, m_data.end(), text);
//	if (it != m_data.end())
//	{
//		return std::distance(m_data.begin(), it);
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//BOOL UListBox::SetSelect(UINT nSel)
//{
//	if (nSel < m_data.size()) {
//		m_sel = nSel;
//		return Show();
//	}
//	else {
//		return FALSE;
//	}
//}
//
//INT UListBox::GetSelect()
//{
//	return m_sel;
//}
//
//BOOL UListBox::UpdateScroll()
//{
//	UINT pos = m_scroll.GetPos();
//	m_scroll.SetRange(m_data.size() - (UINT)((long double)m_rect.h / (long double)20));
//	m_scroll.SetPos(pos);
//	m_scroll.Show();
//	return TRUE;
//}
//
//BOOL UListBox::GetStringRect(URect* rc, UINT n)
//{
//	if (n < m_scroll.GetPos() || n>m_scroll.GetPos() + (UINT)((long double)m_rect.h / (long double)20) || n >= m_data.size()) {
//		return FALSE;
//	}
//	rc->l = m_rect.l + 1;
//	rc->t = m_rect.t + 20 * (n - m_scroll.GetPos()) + 1;
//	rc->w = m_rect.w - 22;
//	rc->h = 19;
//	return TRUE;
//}
//
//BOOL UListBox::IsInScroll(POINT* p)
//{
//	URect rcScroll;
//	m_scroll.GetRect(&rcScroll);
//	return rcScroll.PointInRect(p);
//}
//
//BOOL UListBox::Create(UDialog* pDialog, URect* rc, DLGMSGFUNC onSelChange)
//{
//	m_onSelChange = onSelChange;
//	m_scroll.CreateInner(pDialog, this, &URect{ rc->r() - 20,rc->t + 1,20,rc->h - 1 }, 1, 1, OnSelChange);
//	return UItem::Create(pDialog, rc);
//}
//
//BOOL UListBox::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	m_scroll.Show();
//	UINT pos = m_scroll.GetPos();
//	URect rcText;
//	UINT size = m_data.size();
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		POINT p;
//		GetDlgCursorPos(&p);
//		if (IsInScroll(&p)) {
//			ShowBackGround(CR_LB_FOCUS);
//			UINT size = m_data.size();
//			for (UINT i = pos; i < pos + (UINT)((long double)m_rect.h / (long double)20) && i < size; i++) {
//				GetStringRect(&rcText, i);
//				if (i == m_sel) {
//					DrawStringNoborderRect(&rcText, m_data[i], CT_LB_CLICK);
//				}
//				else {
//					DrawStringNoborderRect(&rcText, m_data[i], CT_LB_FORMAL);
//				}
//			}
//		}
//		else {
//			m_rect.DialogToItem(&p);
//			UINT nFocus = (UINT)((long double)p.y / (long double)20) + pos;
//			ShowBackGround(CR_LB_FOCUS);
//			UINT size = m_data.size();
//			for (UINT i = pos; i < pos + (UINT)((long double)m_rect.h / (long double)20) && i < size; i++) {
//				GetStringRect(&rcText, i);
//				if (i == nFocus && i != m_sel) {
//					DrawStringRect(&rcText, m_data[i], CT_LB_FOCUS);
//				}
//				else if (i == m_sel) {
//					DrawStringNoborderRect(&rcText, m_data[i], CT_LB_CLICK);
//				}
//				else {
//					DrawStringNoborderRect(&rcText, m_data[i], CT_LB_FORMAL);
//				}
//			}
//		}
//		break;
//	case UWS_DISABLE:
//		ShowBackGround(CR_LB_DISABLE);
//		for (UINT i = pos; i < pos + (UINT)((long double)m_rect.h / (long double)20) && i < size; i++) {
//			GetStringRect(&rcText, i);
//			if (i == m_sel) {
//				DrawStringNoborderRect(&rcText, m_data[i], CT_LB_SELDISABLE);
//			}
//			else {
//				DrawStringNoborderRect(&rcText, m_data[i], CT_LB_DISABLE);
//			}
//		}
//		break;
//	case UWS_FORMAL:
//	default:
//		ShowBackGround(CR_LB_FORMAL);
//		for (UINT i = pos; i < pos + (UINT)((long double)m_rect.h / (long double)20) && i < size; i++) {
//			GetStringRect(&rcText, i);
//			if (i == m_sel) {
//				DrawStringNoborderRect(&rcText, m_data[i], CT_LB_CLICK);
//			}
//			else {
//				DrawStringNoborderRect(&rcText, m_data[i], CT_LB_FORMAL);
//			}
//		}
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UListBox::SetShowMode(UITEMSTATE showmode)
//{
//	BOOL bRet = UItem::SetShowMode(showmode);
//	bRet &= m_scroll.SetShowMode(showmode);
//	return bRet;
//}
//
//BOOL UListBox::Update()
//{
//	return Show() && UpdateScroll();
//}
//
//BOOL UListBox::ShowBackGround(COLORREF pen, COLORREF brush)
//{
//	URect rc;
//	rc.l = m_rect.l;
//	rc.t = m_rect.t;
//	rc.w = m_rect.w - 20;
//	rc.h = m_rect.h;
//	return DrawNoborderRect(&rc, brush) && DrawTransparentRect(&m_rect, pen);
//}
//
//BOOL UListBox::OnSelChange(UDialog* dlg, UItem* t)
//{
//	if (t->GetShowMode() == UWS_HIDE || t->GetShowMode() == UWS_DISABLE)return FALSE;
//	t->SetShowMode(UWS_FORMAL);
//	return TRUE;
//}
//
//BOOL UListBox::OnMouse()
//{
//	if (UItem::OnMouse()) {
//		POINT p;
//		GetDlgCursorPos(&p);
//		if (IsInScroll(&p)) {
//			m_scroll.OnMouse();
//		}
//		else {
//			m_scroll.SetShowMode(UWS_FORMAL);
//		}
//	}
//}
//
//BOOL UListBox::OnLClick()
//{
//	if (m_show == UWS_HIDE || m_show == UWS_DISABLE || m_show == UWS_TARGET)return FALSE;
//	m_show = UWS_CLICK;
//	POINT p;
//	GetDlgCursorPos(&p);
//	if (IsInScroll(&p)) {
//		return m_scroll.OnLClick();
//	}
//	m_rect.DialogToItem(&p);
//	UINT pos = m_scroll.GetPos();
//	m_sel = (UINT)((long double)p.y / (long double)20) + pos;
//	if (m_sel >= m_data.size()) {
//		m_sel = -1;
//	}
//	return TRUE;
//}
//
//BOOL UListBox::OnDisable()
//{
//	if (UItem::OnDisable()) {
//		m_scroll.OnDisable();
//		return TRUE;
//	}
//	return FALSE;
//}
//
////BOOL UHScrollBar::SetPos(UINT pos)
////{
////	m_pos = (UINT)((long double)pos / m_range) * (m_rect.w - 40 - m_barWidth / 2);
////	UINT min;
////	UINT max;
////	GetBarRange(&min, &max);
////	if (min > m_pos + 20 + m_rect.l) {
////		m_pos = m_barWidth / 2;
////	}
////	if (m_pos + 20 + m_rect.l > max) {
////		m_pos = m_rect.w - 40 - m_barWidth / 2;
////	}
////	return TRUE;
////}
////
////UINT UHScrollBar::GetPos()
////{
////	return (UINT)((long double)m_pos / (long double)(m_rect.w - 40 - m_barWidth / 2) * (long double)m_range);
////}
////
////BOOL UHScrollBar::UpPos()
////{
////	m_pos -= (UINT)((long double)m_step / (long double)m_range * (long double)(m_rect.w - 40 - m_barWidth/* / 2*/));
////	UINT min;
////	UINT max;
////	GetBarRange(&min, &max);
////	if (min > m_pos + 20 + m_rect.l) {
////		m_pos = m_barWidth / 2;
////	}
////	return TRUE;
////}
////
////BOOL UHScrollBar::DownPos()
////{
////	m_pos += (UINT)((long double)m_step / (long double)m_range * (long double)(m_rect.w - 40 - m_barWidth/* / 2*/));
////	UINT min;
////	UINT max;
////	GetBarRange(&min, &max);
////	if (m_pos + 20 + m_rect.l > max) {
////		m_pos = m_rect.w - 40 - m_barWidth / 2;
////	}
////	return TRUE;
////}
////
////BOOL UHScrollBar::SetRange(UINT range)
////{
////	m_range = range;
////	m_barWidth = max(((m_rect.w - 40) / m_range), 20);
////	return Show();
////}
////
////UINT UHScrollBar::GetRange()
////{
////	return m_range;
////}
////
////BOOL UHScrollBar::SetStep(UINT rangeOfAStep)
////{
////	m_step = rangeOfAStep;
////	return TRUE;
////}
////
////UINT UHScrollBar::GetStep()
////{
////	return m_step;
////}
////
////BOOL UHScrollBar::GetUpRect(URect* rc)
////{
////	rc->l = m_rect.l;
////	rc->t = m_rect.t;
////	rc->w = 20;
////	rc->h = m_rect.h;
////	return TRUE;
////}
////
////BOOL UHScrollBar::GetDownRect(URect* rc)
////{
////	rc->l = m_rect.r() - 20;
////	rc->t = m_rect.t;
////	rc->w = 20;
////	rc->h = m_rect.h;
////	return TRUE;
////}
////
////BOOL UHScrollBar::GetBarRect(URect* rc)
////{
////	rc->l = m_rect.l + 20 + /*(long double)*/m_pos/* / (long double)m_rect.w * (long double)(m_rect.w - 40 - m_barWidth)*/ - m_barWidth / 2;
////	rc->t = m_rect.t;
////	rc->w = m_barWidth;
////	rc->h = m_rect.h;
////	return TRUE;
////}
////
////BOOL UHScrollBar::IsInUp(POINT* p)
////{
////	URect rc;
////	GetUpRect(&rc);
////	return rc.PointInRect(p);
////}
////
////BOOL UHScrollBar::IsInDown(POINT* p)
////{
////	URect rc;
////	GetDownRect(&rc);
////	return rc.PointInRect(p);
////}
////
////BOOL UHScrollBar::IsInBar(POINT* p)
////{
////	URect rc;
////	GetBarRect(&rc);
////	return rc.PointInRect(p);
////}
////
////BOOL UHScrollBar::GetBarRange(UINT* l, UINT* r)
////{
////	*l = m_rect.l + 20 + m_barWidth / 2;//!
////	*r = m_rect.r() - 20 - m_barWidth / 2;//!
////	return TRUE;
////}
////
////BOOL UHScrollBar::Create(UDialog* pDialog, URect* rc, UINT range, UINT step, MSGFUNC onPosChange)
////{
////	m_range = range;
////	m_step = step;
////	m_onPosChange = onPosChange;
////	BOOL bRet = UItem::Create(pDialog, rc);
////	m_barWidth = max((m_rect.w / m_range), 20);
////	m_pos = m_barWidth / 2;
////	return bRet;
////}
////
////BOOL UHScrollBar::CreateInner(UDialog* pDialog,URect* rc, UINT range, UINT step, MSGFUNC onPosChange)
////{
////	m_pDialog = pDialog;
////	m_rect = *rc;
////	m_range = range;
////	m_step = step;
////	m_barWidth = max((m_rect.w / m_range), 20);
////	m_pos = m_barWidth / 2;
////	m_onPosChange = onPosChange;
////	return TRUE;
////}
////
////BOOL UHScrollBar::Show()
////{
////	if (UItem::Show() == FALSE){
////		return FALSE;}
////	ShowRect();
////	switch (m_show) {
////	case SM_HIDE:
////		break;
////	case SM_FOCUS:
////		POINT p;
////		GetDlgCursorPos(&p);
////		ShowBar(CB_SB_FOCUS);
////		if (IsInUp(&p)) {
////			//m_lastFocus = BtnUp;
////			ShowUp(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
////			ShowDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////			ShowBar(CB_SB_FOCUS);
////		}
////		else if (IsInDown(&p)) {
////			//m_lastFocus = BtnDown;
////			ShowUp(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////			ShowDown(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
////			ShowBar(CB_SB_FOCUS);
////		}
////		else if (IsInBar(&p)) {
////			//m_lastFocus = Bar;
////			ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////			ShowBar(CB_SB_FOCUSON);
////		}
////		else {
////			//m_lastFocus = Rect;
////			ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////			ShowBar(CB_SB_FOCUS);
////		}
////		break;
////	case SM_DISABLE:
////		ShowUpDown(CB_SB_UD_DISABLE, CT_SB_UD_DISABLE);
////		ShowBar(CB_SB_DISABLE);
////		break;
////	case SM_FORMAL:
////	default:
////		ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowBar(CB_SB_FORMAL);
////		break;
////	}
////	return TRUE;
////}
////
////BOOL UHScrollBar::Up()
////{
////	UpPos();
////	return Show();
////}
////
////BOOL UHScrollBar::Down()
////{
////	DownPos();
////	return Show();
////}
////
////BOOL UHScrollBar::ShowUp(COLORREF rect, COLORREF text)
////{
////	URect rc;
////	GetUpRect(&rc);
////	DrawNoborderRect(&rc, rect);
////	rc.h -= 5;
////	return DrawString(&rc, "<", text);
////}
////
////BOOL UHScrollBar::ShowDown(COLORREF rect, COLORREF text)
////{
////	URect rc;
////	GetDownRect(&rc);
////	DrawNoborderRect(&rc, rect);
////	rc.h -= 5;
////	return DrawString(&rc, ">", text);
////}
////
////BOOL UHScrollBar::ShowUpDown(COLORREF rect, COLORREF text)
////{
////	return ShowUp(rect, text) && ShowDown(rect, text);
////}
////
////BOOL UHScrollBar::ShowBar(COLORREF rect)
////{
////	URect rc;
////	GetBarRect(&rc);
////	return DrawNoborderRect(&rc, rect);
////}
////
////BOOL UHScrollBar::ShowRect()
////{
////	DrawNoborderRect(&m_rect, CR_SB_FORMAL);
////	SetPen(CL_SB_FORMAL);
////	POINT p;
////	MoveToEx(hDC, m_rect.l, m_rect.t - 1, &p);
////	return LineTo(hDC, m_rect.r(), m_rect.t - 1);
////}
////
////VOID UHScrollBar::OnMouse()
////{
////	UItem::OnMouse();
////	
////	POINT p;
////	GetDlgCursorPos(&p);
////
////	ShowRect();
////	if (IsInUp(&p)) {
////		//m_lastFocus = BtnUp;
////		ShowUp(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
////		ShowDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowBar(CB_SB_FOCUS);
////	}
////	else if (IsInDown(&p)) {
////		//m_lastFocus = BtnDown;
////		ShowUp(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowDown(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
////		ShowBar(CB_SB_FOCUS);
////	}
////	else if (IsInBar(&p)) {
////		//m_lastFocus = Bar;
////		ShowUp(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowBar(CB_SB_FOCUSON);
////	}
////	else {
////		//m_lastFocus = Rect;
////		ShowUp(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////		ShowBar(CB_SB_FOCUS);
////	}
////}
////
////VOID UHScrollBar::OnDisable()
////{
////	UItem::OnDisable();
////	
////	ShowRect();
////	ShowUpDown(CB_SB_UD_DISABLE, CT_SB_UD_DISABLE);
////	ShowBar(CB_SB_DISABLE);
////}
////
////VOID UHScrollBar::OnLClick()
////{
////	UItem::OnLClick();
////	
////	
////	POINT p;
////	GetDlgCursorPos(&p);
////	if (IsInUp(&p)) {
////		ShowUp(CB_SB_UD_CLICK, CT_SB_UD_CLICK);
////		UpPos();
////	}
////	else if (IsInDown(&p)) {
////		ShowDown(CB_SB_UD_CLICK, CT_SB_UD_CLICK);
////		DownPos();
////	}
////	else if (IsInBar(&p)) {
////		URect rcBar;
////		GetBarRect(&rcBar);
////		INT oldPos = m_pos;
////		INT toMid = p.x - (rcBar.l + rcBar.w / 2);//!
////		UINT min;
////		UINT max;
////		GetBarRange(&min, &max);
////		m_rect.DialogToItem(&p);
////
////		while (CheckLButton()) {
////			....Sleep(MSG_TIME);
////			m_pDialog->UpdateView();
////			GetDlgCursorPos(&p);
////			p.x -= toMid;
////			if (min < (UINT)p.x && (UINT)p.x < max) {
////				m_rect.DialogToItem(&p);
////				m_pos = (p.x - 20);
////				ShowRect();
////				ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////				ShowBar(CB_SB_CLICK);
////				if (m_onPosChange != nullptr) {
////					m_onPosChange(m_pDialog, this);
////				}
////			}
////		}
////		GetDlgCursorPos(&p);
////		if (isIn(&p)) {
////			OnMouse();
////		}
////		else {
////			ShowRect();
////			ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
////			ShowBar(CB_SB_FORMAL);
////		}
////	}
////}
//
//BOOL UVScrollBar::SetPos(UINT pos)
//{
//	m_pos = (UINT)((long double)pos / m_range) * (m_rect.h - 40);
//	m_pos = MakeInRange(m_pos);
//	return TRUE;
//}
//
//UINT UVScrollBar::GetPos()
//{
//	return (UINT)((long double)m_pos /((long double)m_rect.h - 40) * (long double)m_range);
//}
//
//BOOL UVScrollBar::UpPos()
//{
//	m_pos -= (UINT)((long double)m_step / (long double)m_range * ((long double)m_rect.h - 40));
//	m_pos = MakeInRange(m_pos);
//	return TRUE;
//}
//
//BOOL UVScrollBar::DownPos()
//{
//	m_pos += (UINT)((long double)m_step / (long double)m_range * ((long double)m_rect.h - 40));
//	m_pos = MakeInRange(m_pos);
//	return TRUE;
//}
//
//BOOL UVScrollBar::SetRange(UINT range)
//{
//	m_range = range;
//	return TRUE;
//}
//
//UINT UVScrollBar::GetRange()
//{
//	return m_range;
//}
//
//BOOL UVScrollBar::SetStep(UINT rangeOfAStep)
//{
//	m_step = rangeOfAStep;
//	return TRUE;
//}
//
//UINT UVScrollBar::GetStep()
//{
//	return m_step;
//}
//
//BOOL UVScrollBar::GetUpRect(URect* rc)
//{
//	rc->l = m_rect.l;
//	rc->t = m_rect.t;
//	rc->w = m_rect.w;
//	rc->h = 20;
//	return TRUE;
//}
//
//BOOL UVScrollBar::GetDownRect(URect* rc)
//{
//	rc->l = m_rect.l;
//	rc->t = m_rect.b() - 20;
//	rc->w = m_rect.w;
//	rc->h = 20;
//	return TRUE;
//}
//
//BOOL UVScrollBar::GetBarRect(URect* rc)
//{
//	UINT bh = max((m_rect.h - 40) / (m_range), 20);
//	rc->l = m_rect.l;
//	rc->t = m_rect.t + 20 + m_pos - bh / 2;
//	rc->w = m_rect.w;
//	rc->h = bh;
//	return TRUE;
//}
//
//BOOL UVScrollBar::IsInUp(POINT* p)
//{
//	URect rc;
//	GetUpRect(&rc);
//	return rc.PointInRect(p);
//}
//
//BOOL UVScrollBar::IsInDown(POINT* p)
//{
//	URect rc;
//	GetDownRect(&rc);
//	return rc.PointInRect(p);
//}
//
//BOOL UVScrollBar::IsInBar(POINT* p)
//{
//	URect rc;
//	GetBarRect(&rc);
//	return rc.PointInRect(p);
//}
//
//INT UVScrollBar::MakeInRange(INT pos)
//{
//	INT bh = max((m_rect.h - 40) / (m_range), 20) / 2;
//	if (pos < bh) {
//		return bh;
//	}
//	else if (m_rect.h - bh - 40 < pos) {
//		return m_rect.h - bh - 40;
//	}
//	return pos;
//}
//
//BOOL UVScrollBar::Create(UDialog* pDialog, URect* rc, UINT range, UINT step, DLGMSGFUNC onPosChange)
//{
//	m_range = range;
//	m_step = step;
//	m_onPosChange = onPosChange;
//	BOOL bRet = UItem::Create(pDialog, rc);
//	m_pos = max((m_rect.h - 40) / (m_range), 20) / 2;
//	m_parent = this;
//	return bRet;
//}
//
//BOOL UVScrollBar::CreateInner(UDialog* pDialog, UItem* parent, URect* rc, UINT range, UINT step, DLGMSGFUNC onPosChange)
//{
//	m_pDialog = (UDialog*)pDialog;
//	m_rect = *rc;
//	m_range = range;
//	m_step = step;
//	m_pos = max((m_rect.h - 40) / (m_range), 20) / 2;
//	m_onPosChange = onPosChange;
//	m_parent = parent;
//	return TRUE;
//}
//
//BOOL UVScrollBar::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	ShowRect();
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		POINT p;
//		GetDlgCursorPos(&p);
//		ShowBar(CB_SB_FOCUS);
//		if (IsInUp(&p)) {
//			//m_lastFocus = BtnUp;
//			ShowUp(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
//			ShowDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
//			ShowBar(CB_SB_FOCUS);
//		}
//		else if (IsInDown(&p)) {
//			//m_lastFocus = BtnDown;
//			ShowUp(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
//			ShowDown(CB_SB_UD_FOCUSON, CT_SB_UD_FOCUSON);
//			ShowBar(CB_SB_FOCUS);
//		}
//		else if (IsInBar(&p)) {
//			//m_lastFocus = Bar;
//			ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
//			ShowBar(CB_SB_FOCUSON);
//		}
//		else {
//			//m_lastFocus = Rect;
//			ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
//			ShowBar(CB_SB_FOCUS);
//		}
//		break;
//	case UWS_DISABLE:
//		ShowUpDown(CB_SB_UD_DISABLE, CT_SB_UD_DISABLE);
//		ShowBar(CB_SB_DISABLE);
//		break;
//	case UWS_FORMAL:
//	default:
//		ShowUpDown(CB_SB_UD_FORMAL, CT_SB_UD_FORMAL);
//		ShowBar(CB_SB_FORMAL);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UVScrollBar::Up()
//{
//	UpPos();
//	return Show();
//}
//
//BOOL UVScrollBar::Down()
//{
//	DownPos();
//	return Show();
//}
//
//BOOL UVScrollBar::ShowUp(COLORREF rect, COLORREF text)
//{
//	URect rc;
//	GetUpRect(&rc);
//	DrawNoborderRect(&rc, rect);
//	//rc.h -= 5;
//	return DrawString(&rc, "¨u¨v", text);
//}
//
//BOOL UVScrollBar::ShowDown(COLORREF rect, COLORREF text)
//{
//	URect rc;
//	GetDownRect(&rc);
//	DrawNoborderRect(&rc, rect);
//	//rc.h -= 5;
//	return DrawString(&rc, "¨v¨u", text);
//}
//
//BOOL UVScrollBar::ShowUpDown(COLORREF rect, COLORREF text)
//{
//	return ShowUp(rect, text) && ShowDown(rect, text);
//}
//
//BOOL UVScrollBar::ShowBar(COLORREF rect)
//{
//	URect rc;
//	GetBarRect(&rc);
//	return DrawNoborderRect(&rc, rect);
//}
//
//BOOL UVScrollBar::ShowRect()
//{
//	DrawNoborderRect(&m_rect, CR_SB_FORMAL);
//	SetPen(CL_SB_FORMAL);
//	POINT p;
//	MoveToEx(hDC, m_rect.l - 1, m_rect.t, &p);
//	return LineTo(hDC, m_rect.l - 1, m_rect.b() - 1);
//}
//
//BOOL UVScrollBar::OnLClick()
//{
//	if (m_show == UWS_HIDE || m_show == UWS_DISABLE || m_show == UWS_TARGET)return FALSE;
//	m_show = UWS_CLICK;
//	POINT p;
//	GetDlgCursorPos(&p);
//	if (IsInUp(&p)) {
//		WaitLButtonUp();
//		UpPos();
//	}
//	else if (IsInDown(&p)) {
//		WaitRButtonUp();
//		DownPos();
//	}
//	else if (IsInBar(&p)) {
//		URect rcBar;
//		GetBarRect(&rcBar);
//		INT oldPos = m_pos;
//		INT toMid = p.y - (rcBar.t + rcBar.h / 2);
//		INT lastpos = m_pos;
//		while (CheckLButton()) {
//			m_pDialog->WaitTime();
//			m_pDialog->UpdateView();
//			GetDlgCursorPos(&p);
//			p.y -= toMid;
//			m_pos = p.y - m_rect.t - 20;
//			m_pos = MakeInRange(m_pos);
//			if (m_onPosChange != nullptr && m_pos != lastpos) {
//				m_onPosChange(m_pDialog, m_parent);
//			}
//			lastpos = m_pos;
//		}
//	}
//	return TRUE;
//}
//
//BOOL USliderControl::SetPos(UINT pos)
//{
//	m_pos = pos;
//	if (m_pos < m_min) {
//		m_pos = m_min;
//	}
//	else if (m_pos > m_max) {
//		m_pos = m_max;
//	}
//	return TRUE;
//}
//
//UINT USliderControl::GetPos()
//{
//	return m_pos;
//}
//
//BOOL USliderControl::SetTick(UINT pos)
//{
//	m_tick.push_back(pos);
//	return TRUE;
//}
//
//BOOL USliderControl::SetTickFreq(UINT freq)
//{
//	for (UINT i = m_min; i <= m_max; i += freq) {
//		m_tick.push_back(i);
//	}
//	return TRUE;
//}
//
//BOOL USliderControl::GetTick(std::vector<UINT>* tick)
//{
//	*tick = m_tick;
//	return TRUE;
//}
//
//BOOL USliderControl::SetRange(UINT min, UINT max)
//{
//	m_min = min;
//	m_max = max;
//	if (m_min >= m_max) {
//		return FALSE;
//	}
//	return TRUE;
//}
//
//BOOL USliderControl::GetRange(UINT* min, UINT* max)
//{
//	*min = m_min;
//	*max = m_max;
//	return TRUE;
//}
//
//BOOL USliderControl::GetBarRect(URect* rc)
//{
//	rc->l = PosToPoint(m_pos) - 8;
//	rc->t = m_rect.t + 4;
//	rc->w = 16;
//	rc->h = 28;
//	return TRUE;
//}
//
//BOOL USliderControl::GetChannelRect(URect* rc)
//{
//	rc->l = m_rect.l;
//	rc->t = m_rect.t + 15;
//	rc->w = m_rect.w;
//	rc->h = 5;
//	return TRUE;
//}
//
//BOOL USliderControl::GetFilledRect(URect* rc)
//{
//	rc->l = m_rect.l;
//	rc->t = m_rect.t + 16;
//	rc->w = PosToPoint(m_pos) - 8 - m_rect.l;
//	rc->h = 4;
//	return TRUE;
//}
//
//BOOL USliderControl::IsInBar(POINT* p)
//{
//	URect rc;
//	GetBarRect(&rc);
//	return rc.PointInRect(p);
//}
//
//BOOL USliderControl::IsInChannel(POINT* p)
//{
//	URect rc;
//	GetChannelRect(&rc);
//	return rc.PointInRect(p);
//}
//
//INT USliderControl::PosToPoint(UINT pos)
//{
//	INT p = m_rect.l + (INT)(8 + (((long double)m_rect.w - 16) * (long double)pos / (long double)(m_max - m_min/* + 1*/)));
//	if (m_rect.r() - 8 <= p) {
//		p = m_rect.r() - 9;
//	}
//	return p;
//}
//
//UINT USliderControl::PointToPos(INT point)
//{
//	return (UINT)(((long double)m_max - m_min + 1) * ((long double)point - m_rect.l - 8) / ((long double)m_rect.w - 16));
//}
//
//BOOL USliderControl::Create(UDialog* pDialog, URect* rc, UINT min, UINT max, BOOL filled, DLGMSGFUNC onPosChange)
//{
//	m_min = min;
//	m_max = max;
//	m_filled = filled;
//	m_onPosChange = onPosChange;
//	return UItem::Create(pDialog, rc);
//}
//
//BOOL USliderControl::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	POINT p;
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//		ShowBackGround();
//		ShowTick();
//	case UWS_FOCUS:
//		GetDlgCursorPos(&p);
//		if (IsInBar(&p)) {
//			ShowChannel(CR_SC_CHN_FORMAL);
//			ShowBar(CR_SC_BAR_FOCUS);
//		}
//		else if (IsInChannel(&p)) {
//			ShowChannel(CR_SC_CHN_FOCUS);
//			ShowBar(CR_SC_BAR_FORMAL);
//		}
//		else {
//			ShowChannel(CR_SC_CHN_FORMAL);
//			ShowBar(CR_SC_BAR_FORMAL);
//		}
//		break;
//	case UWS_CLICK:
//		GetDlgCursorPos(&p);
//		if (IsInBar(&p)) {
//			ShowChannel(CR_SC_CHN_FORMAL);
//			ShowBar(CR_SC_BAR_CLICK);
//		}
//		else if (IsInChannel(&p)) {
//			ShowChannel(CR_SC_CHN_FOCUS);
//			ShowBar(CR_SC_BAR_FORMAL);
//		}
//		else {
//			ShowChannel(CR_SC_CHN_FORMAL);
//			ShowBar(CR_SC_BAR_FORMAL);
//		}
//		break;
//	case UWS_DISABLE:
//		ShowChannel(CR_SC_CHN_DISABLE);
//		ShowBar(CR_SC_BAR_DISABLE);
//		break;
//	case UWS_FORMAL:
//	default:
//		ShowChannel(CR_SC_CHN_FORMAL);
//		ShowBar(CR_SC_BAR_FORMAL);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL USliderControl::ShowBackGround()
//{
//	return DrawNoborderRect(&m_rect, CB_WINDOW);
//}
//
//BOOL USliderControl::ShowTick()
//{
//	UINT s = m_tick.size();
//	POINT p;
//	SetPen(CL_SC_TICK_FORMAL);
//	BOOL bRet = TRUE;
//	for (UINT i = 0; i < s; i++) {
//		bRet &= MoveToEx(hDC,/*  8 + */PosToPoint(m_tick[i]), m_rect.t, &p);
//		bRet &= LineTo(hDC, /* 8 +*/ PosToPoint(m_tick[i]), m_rect.t + 3);
//		//bRet &= MoveToEx(hDC,/*  8 + */PosToPoint(m_tick[i]), m_rect.t + 34, &p);
//		//bRet &= LineTo(hDC, /* 8 +*/ PosToPoint(m_tick[i]), m_rect.t + 37);
//	}
//	return bRet;
//}
//
//BOOL USliderControl::ShowChannel(COLORREF pen, COLORREF brush, COLORREF fill)
//{
//	URect rc;
//	BOOL bRet = TRUE;
//	bRet &= GetChannelRect(&rc);
//	bRet &= DrawRect(&rc, pen, brush);
//	if (m_filled) {
//		bRet &= GetFilledRect(&rc);
//		bRet &= DrawNoborderRect(&rc, fill);
//	}
//	return bRet;
//}
//
//BOOL USliderControl::ShowBar(COLORREF pen, COLORREF brush)
//{
//	URect rc;
//	GetBarRect(&rc);
//	return DrawRect(&rc, pen, brush);
//}
//
//BOOL USliderControl::OnLClick()
//{
//	if (m_show == UWS_HIDE || m_show == UWS_DISABLE || m_show == UWS_TARGET)return FALSE;
//	m_show = UWS_CLICK;
//	POINT p;
//	INT lastPos = -1;
//	GetDlgCursorPos(&p);
//	if (IsInBar(&p)) {
//		while (CheckLButton()) {
//			m_pDialog->WaitTime();
//			m_pDialog->UpdateView();
//			GetDlgCursorPos(&p);
//			if ((m_rect.l + 8) < p.x && p.x < (m_rect.r() - 8)) {
//				m_pos = PointToPos(p.x);
//				if (m_pos != lastPos) {
//					if (m_onPosChange != nullptr) {
//						m_onPosChange(m_pDialog, this);
//					}
//				}
//				lastPos = m_pos;
//			}
//		}
//	}
//	else if (IsInChannel(&p)) {
//		lastPos = m_pos;
//		GetDlgCursorPos(&p);
//		if ((m_rect.l + 8) > p.x) {
//			p.x = m_rect.l + 8;
//		}
//		else if (p.x > (m_rect.r() - 8)) {
//			p.x = m_rect.r() - 8;
//		}
//		m_pos = PointToPos(p.x);
//		if (m_pos != lastPos) {
//			if (m_onPosChange != nullptr) {
//				m_onPosChange(m_pDialog, this);
//			}
//		}
//	}
//	return TRUE;
//}
//
//BOOL UTest::Create(UDialog* pDialog, URect* rc)
//{
//	UItem::Create(pDialog, rc);
//	return SetKeyCall();
//}
//
//
//VOID UTest::OnKey(KEY_EVENT_RECORD* k)
//{
//
//	//Ò»¶Ñ²Ù×÷
//	UItem::OnKey(k);
//}
//
//STRING UNumEdit::GetNumString()
//{
//	if (m_isFloat) {
//		//return std::to_string(m_num.f);
//		//char* c = new char[m_max + 10];
//		//sprintf_s(c, m_max + 10, "%g", (float)m_num.f);
//		//STRING s (c);
//		//delete[] c;
//		STRING s = std::to_string(m_num.f);
//		size_t w = s.find('.');
//		for (size_t i = s.length() - 1; i > w; i--) {
//			if (s[i] == '0') {
//				s[i] = '\0';
//			}
//			else {
//				return s;
//			}
//		}
//		s[w] = '\0';
//		return s;
//	}
//	else {
//		return std::to_string(m_num.i);
//	}
//}
//
//BOOL UNumEdit::SetMax(INT max)
//{
//	m_max = max;
//	return TRUE;
//}
//
//INT UNumEdit::GetMax()
//{
//	return m_max;
//}
//
//BOOL UNumEdit::GetNumRect(URect* rcNum)
//{
//	*rcNum = m_rect;
//	return TRUE;
//}
//
//BOOL UNumEdit::Create(UDialog* pDialog, URect* rc, FLOAT num, BOOL isFloat, INT max, DLGMSGFUNC onNumChange)
//{
//	m_isFloat = isFloat;
//	if (m_isFloat) {
//		m_num.f = num;
//	}
//	else {
//		m_num.i = (INT)num;
//	}
//	m_max = max;
//	m_onNumChange = onNumChange;
//	UItem::Create(pDialog, rc);
//	return SetKeyCall();
//}
//
//BOOL UNumEdit::Show()
//{
//	if (UItem::Show() == FALSE) {
//		return FALSE;
//	}
//	URect rcNum;
//	GetNumRect(&rcNum);
//	switch (m_show) {
//	case UWS_HIDE:
//		break;
//	case UWS_FOCUS:
//		DrawRect(&m_rect, CR_NE_FOCUS);
//		DrawString(&rcNum, GetNumString(), CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//		break;
//	case UWS_DISABLE:
//		Draw2BorderRect(&m_rect, CR_NE_DISABLE);
//		DrawString(&rcNum, GetNumString(), CT_NE_DISABLE, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//		break;
//	case UWS_TARGET:
//		DrawRect(&m_rect, CR_NE_TARGET);
//		DrawString(&rcNum, GetNumString(), CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//		break;
//	case UWS_FORMAL:
//	default:
//		DrawRect(&m_rect, CR_NE_FORMAL);
//		DrawString(&rcNum, GetNumString(), CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//		break;
//	}
//	return TRUE;
//}
//
//BOOL UNumEdit::OnMouse()
//{
//	if (UItem::OnMouse()) {
//		if (m_curState == FALSE) {
//			SetCursor(IDC_IBEAM);
//			m_curState = TRUE;
//		}
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL UNumEdit::OnMouseLeave()
//{
//	if (UItem::OnMouseLeave()) {
//		if (m_curState == TRUE) {
//			SetCursor(IDC_ARROW);
//			m_curState = FALSE;
//		}
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL UNumEdit::OnLClick()
//{
//	if (UItem::OnLClick()) {
//		return UItem::SetTarget();
//	}
//	return FALSE;
//}
//
//VOID UNumEdit::OnKey(KEY_EVENT_RECORD* k)
//{
//	UItem::OnKey(k);
//	if (m_show == UWS_TARGET)
//	{
//		if (k->bKeyDown)
//		{
//			if (isdigit(k->uChar.AsciiChar))//ÅÐ¶ÏÊý×Ö
//			{
//				STRING oString;
//				if (m_isFloat ? m_num.f == 0.0 : m_num.i == 0)
//				{
//					oString = k->uChar.AsciiChar; DrawStringNoborderRect(&URect{ 0,0,100,20 }, "!!!!!!!!!!!!!!!!!!!!!!!!!", RGB(0, 0, 0));///
//				}
//				else {
//
//					oString = GetNumString() + k->uChar.AsciiChar; DrawStringNoborderRect(&URect{ 0,0,100,20 }, "!" + oString, RGB(0, 0, 0));///
//				}
//				DrawStringNoborderRect(&URect{ 100,0,100,20 }, "?" + oString, RGB(0, 0, 0));///
//				if (m_isFloat)
//				{
//					if (oString.length() > (size_t)m_max) {
//						MessageBeep(MB_ICONEXCLAMATION);
//						return;
//					}
//					sscanf_s(oString.c_str(), "%lf", &(m_num.f));
//				}
//				else
//				{
//					if (oString.length() > (size_t)m_max) {
//						MessageBeep(MB_ICONEXCLAMATION);
//						return;
//					}
//					sscanf_s(oString.c_str(), "%lld", &(m_num.i));
//				}
//				STRING newString = GetNumString();
//				if (strcmp(oString.c_str(), newString.c_str())) {
//					MessageBeep(MB_ICONEXCLAMATION);
//					return;
//				}
//				if (m_onNumChange != nullptr) {
//					m_onNumChange(m_pDialog, this);
//				}
//				DrawRect(&m_rect, CR_NE_TARGET);
//				URect rcNum;
//				GetNumRect(&rcNum);
//				DrawString(&rcNum, newString, CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//			}
//			else if (k->uChar.AsciiChar == '.')//ÅÐ¶Ïµã£¨FLOAT only£©
//			{
//				if (m_isFloat) {
//					STRING oString = GetNumString();
//					if (oString.find('.') != oString.npos) {
//						MessageBeep(MB_ICONEXCLAMATION);
//						return;
//					}
//					oString += '.';
//					sscanf_s(oString.c_str() + '0', "%lf", &(m_num.f));
//					//STRING newString = GetNumString();
//					DrawStringNoborderRect(&URect{ 0,0,100,20 }, oString, RGB(0, 0, 0));///
//					//if (oString != newString) {
//					//	MessageBeep(MB_ICONEXCLAMATION);
//					//	return;
//					//}
//					if (m_onNumChange != nullptr) {
//						m_onNumChange(m_pDialog, this);
//					}
//					DrawRect(&m_rect, CR_NE_TARGET);
//					URect rcNum;
//					GetNumRect(&rcNum);
//					DrawString(&rcNum, oString, CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//				}
//				else {
//					MessageBeep(MB_ICONEXCLAMATION);
//				}
//			}
//			else if (k->uChar.AsciiChar == '\b')//ÅÐ¶ÏÍË¸ñ
//			{
//				STRING oString = GetNumString();
//				size_t len = oString.length();
//				if (len < 1) {
//					MessageBeep(MB_ICONEXCLAMATION);
//				}
//				else if (len == 1) {
//					if (m_isFloat) {
//						m_num.f = 0.0;
//					}
//					else {
//						m_num.i = 0;
//					}
//					if (m_onNumChange != nullptr) {
//						m_onNumChange(m_pDialog, this);
//					}
//					DrawRect(&m_rect, CR_NE_TARGET);
//					URect rcNum;
//					GetNumRect(&rcNum);
//					DrawString(&rcNum, GetNumString(), CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//				}
//				else {
//					//oString = oString.substr(0, oString.length() - 1);
//					oString[oString.length() - 1] = '\0';
//					DrawStringNoborderRect(&URect(0, 0, 100, 20), oString);
//
//					if (m_isFloat) {
//						if (oString.length() > (size_t)m_max) {
//							MessageBeep(MB_ICONEXCLAMATION);
//							return;
//						}
//						sscanf_s(oString.c_str(), "%lf", &(m_num.f));
//					}
//					else {
//						if (oString.length() > (size_t)m_max) {
//							MessageBeep(MB_ICONEXCLAMATION);
//							m_num.i = 0;
//							return;
//						}
//						sscanf_s(oString.c_str(), "%lld", &(m_num.i));
//					}
//					if (m_onNumChange != nullptr) {
//						m_onNumChange(m_pDialog, this);
//					}
//					DrawRect(&m_rect, CR_NE_TARGET);
//					URect rcNum;
//					GetNumRect(&rcNum);
//					DrawString(&rcNum, GetNumString(), CT_NE_FORMAL, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
//				}
//			}
//			else if (isalpha(k->uChar.AsciiChar)) {
//				MessageBeep(MB_ICONEXCLAMATION);
//			}
//		}
//	}
//}

