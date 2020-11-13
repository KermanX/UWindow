#pragma once

#ifndef UITEM_H
#define UITEM_H


#include "UWindowDef.h"
#include "UWidget.h"

#pragma warning(disable:26812)

class UItem : public UWidget
{

	//Constructors
public:
	INLINE UItem() {
		m_pDialog = nullptr;
		m_keyCall = nullptr;
		m_type = Default;
		m_next = NULL;
	}

	//Attributes
protected:
	UDialog* m_pDialog;
	UItem* m_keyCall;
	URect m_rect;
	ITEMTYPE m_type;
	UItemState  m_state;
public:
	INLINE ITEMTYPE GetType() {
		return m_type;
	}

	//Data
protected:
	UItem* m_next;
public:
	INLINE UItem* GetNext() {
		return m_next;
	}

	//Operations
public:
	virtual BOOL Create(UDialog* pDialog, URect* rc);
protected:
	virtual BOOL SetKeyCall();
	virtual BOOL SetTarget();
	virtual BOOL IsIn(POINT* p);

	//Messages
public:
	virtual BOOL OnTimer();
	virtual BOOL OnMouseMove(POINT* p);
	virtual BOOL OnLDown(POINT* p);
	virtual BOOL OnLUp(POINT* p);
	virtual BOOL OnLClick(POINT* p);
	virtual BOOL OnRDown(POINT* p);
	virtual BOOL OnRUp(POINT* p);
	virtual BOOL OnRClick(POINT* p);
	virtual BOOL OnKey(KEY_EVENT_RECORD* k);
	virtual BOOL OnWhelled(POINT* p, UINT n);
	virtual BOOL OnString(STRING* s);
	virtual BOOL OnShow(UPaint* p);
	virtual BOOL OnNoTarget();
};

class UButton :
	public UItem
{
	//Constructors
public:
	INLINE UButton() {
		m_type = Button;
		m_onLClick = nullptr;
		m_onRClick = nullptr;
		m_dState = 100;
		m_dDelta = 0;
	}

	//Attributes
protected:
	STRING m_text;
public:
	virtual BOOL SetText(STRING text);
	virtual STRING GetText();

	//Callbacks
protected:
	DLGMSGFUNC m_onLClick;
	DLGMSGFUNC m_onRClick;

	//Operations
public:
	virtual BOOL Create(UDialog* pDialog, URect* rc, STRING text, DLGMSGFUNC onLClick = nullptr, DLGMSGFUNC onRClick = nullptr);

	//Display
protected:
	INT m_dState;
	INT m_dDelta;

	//Messages
public:
	virtual BOOL OnTimer();
	virtual BOOL OnMouseMove(POINT* p);
	virtual BOOL OnLDown(POINT* p);
	virtual BOOL OnLUp(POINT* p);
	virtual BOOL OnLClick(POINT* p);
	virtual BOOL OnRDown(POINT* p);
	virtual BOOL OnRUp(POINT* p);
	virtual BOOL OnRClick(POINT* p);
	virtual BOOL OnShow(UPaint* p);
};
//
//class UCheckBox :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UCheckBox() {
//		m_type = CheckBox;
//		m_isCheck = FALSE;
//		m_onLClick = nullptr;
//	}
//
//	//Attributes
//protected:
//	BOOL m_isCheck;
//	STRING m_text;
//public:
//	virtual BOOL SetCheck(BOOL isCheck = TRUE);
//	virtual BOOL GetCheck();
//protected:
//	virtual BOOL GetCheckRect(URect* rc);
//	virtual BOOL GetTextRect(URect* rc);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, STRING text, DLGMSGFUNC onLClick = nullptr, BOOL isCheck = FALSE);
//	virtual BOOL Show();
//	virtual BOOL Check();
//protected:
//	virtual BOOL DrawCheckRect(COLORREF pen, COLORREF brush);
//
//	//Callbacks
//protected:
//	DLGMSGFUNC m_onLClick = nullptr;
//
//	//Messages
//public:
//	virtual BOOL OnLClick();
//};
//
//class UStaticText :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UStaticText() {
//		m_type = StaticText;
//		m_color = RGB(0, 0, 0);
//		m_edge = FALSE;
//		m_isTransparent = FALSE;
//		m_format = 2085U;
//	}
//
//	//Attributes
//protected:
//	COLORREF m_color;
//	BOOL m_isTransparent;
//	BOOL m_edge;
//	UINT m_format;
//	STRING m_text;
//public:
//	virtual BOOL SetText(STRING text);
//	virtual STRING GetText();
//	virtual BOOL SetMode(BOOL isTransparent = 0, COLORREF color = RGB(0, 0, 0), BOOL edge = FALSE, UINT format = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
//	virtual BOOL GetMode(BOOL* isTransparent, COLORREF* color = nullptr, BOOL* edge = nullptr, UINT* format = nullptr);
//
//	//Display
//protected:
//	virtual BOOL ShowString();
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, STRING text, BOOL edge = FALSE, BOOL isTransparent = 0, COLORREF color = RGB(0, 0, 0), UINT format = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
//	virtual BOOL Show();
//};
//
//class UProgressBar :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UProgressBar() {
//		m_type = ProgressBar;
//		m_range = 100;
//		m_step = 1;
//		m_pos = 0;
//	}
//
//	//Data
//protected:
//	UINT m_pos;
//public:
//	virtual BOOL SetPos(UINT pos);
//	virtual UINT GetPos();
//	virtual BOOL SetPercent(long double percent);
//	virtual long double GetPersent();
//
//	//Attributes
//protected:
//	UINT m_range;
//	UINT m_step;
//public:
//	virtual BOOL SetRange(UINT range);
//	virtual UINT GetRange();
//	virtual BOOL SetStep(UINT rangeOfAStep);
//	virtual UINT GetStep();
//	virtual BOOL Error(BOOL isError = TRUE);
//	virtual BOOL Pause(BOOL isPause = TRUE);
//protected:
//	virtual BOOL GetBarRect(URect* rcBar);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, UINT range = 100, UINT step = 1);
//	virtual BOOL Show();
//	virtual BOOL Step();
//};
////
////class UHScrollBar :
////	public UItem 
////{
////	//Constructors
////public:
////	INLINE UHScrollBar() {
////		m_type = HScrollBar;
////		m_range = 100;
////		m_step = 1;
////		m_barWidth = max(((m_rect.w - 40) / m_range), 20);
////		m_pos = m_barWidth/2;
////		//m_lastFocus = None;
////		m_onPosChange = nullptr;
////	}
////
////	//Data
////protected:
////	UINT m_pos;	//As PX
////	UINT m_barWidth;
////	//enum {
////	//	Rect,
////	//	BtnUp,
////	//	BtnDown,
////	//	Bar,
////	//	None
////	//}m_lastFocus;
////public:
////	virtual BOOL SetPos(UINT pos);
////	virtual UINT GetPos();
////protected:
////	virtual BOOL UpPos();
////	virtual BOOL DownPos();
////
////	//Attributes
////protected:
////	UINT m_range;	//As var
////	UINT m_step;	//As var
////public:
////	virtual BOOL SetRange(UINT range);
////	virtual UINT GetRange();
////	virtual BOOL SetStep(UINT rangeOfAStep);
////	virtual UINT GetStep();
////protected:
////	virtual BOOL GetUpRect(URect* rc);
////	virtual BOOL GetDownRect(URect* rc);
////	virtual BOOL GetBarRect(URect* rc);
////	virtual BOOL IsInUp(POINT* p);
////	virtual BOOL IsInDown(POINT* p);
////	virtual BOOL IsInBar(POINT* p);
////	virtual BOOL GetBarRange(UINT* l, UINT* r);
////
////	//Operations
////public:
////	virtual BOOL Create(UDialog* pDialog, URect* rc, UINT range = 100, UINT step = 1, MSGFUNC onPosChange = nullptr);
////	virtual BOOL CreateInner(UDialog* pDialog, URect* rc, UINT range = 100, UINT step = 1, MSGFUNC onPosChange = nullptr);
////	virtual BOOL Show();
////	virtual BOOL Up();
////	virtual BOOL Down();
////
////	//Display
////protected:
////	virtual BOOL ShowUp(COLORREF rect,COLORREF text);
////	virtual BOOL ShowDown(COLORREF rect, COLORREF text);
////	virtual BOOL ShowUpDown(COLORREF rect, COLORREF text);
////	virtual BOOL ShowBar(COLORREF rect);
////	virtual BOOL ShowRect();
////
////	//Callbacks
////public:
////	MSGFUNC m_onPosChange;
////
////	//Messages
////public:
////	virtual VOID OnMouse();
////	virtual VOID OnDisable();
////	virtual VOID OnLClick();
////};
//
//class UVScrollBar :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UVScrollBar() {
//		m_type = VScrollBar;
//		m_range = 1;
//		m_step = 1;
//		m_pos = 10;
//		//m_lastFocus = None;
//		m_onPosChange = nullptr;
//		m_parent = nullptr;
//	}
//
//	//Data
//protected:
//	UINT m_pos;
//	UItem* m_parent;
//	//enum {
//	//	Rect,
//	//	BtnUp,
//	//	BtnDown,
//	//	Bar,
//	//	None
//	//}m_lastFocus;
//public:
//	virtual BOOL SetPos(UINT pos);
//	virtual UINT GetPos();
//	virtual BOOL UpPos();
//	virtual BOOL DownPos();
//
//	//Attributes
//protected:
//	UINT m_range;	//As var
//	UINT m_step;	//As var
//public:
//	virtual BOOL SetRange(UINT range);
//	virtual UINT GetRange();
//	virtual BOOL SetStep(UINT rangeOfAStep);
//	virtual UINT GetStep();
//protected:
//	virtual BOOL GetUpRect(URect* rc);
//	virtual BOOL GetDownRect(URect* rc);
//	virtual BOOL GetBarRect(URect* rc);
//	virtual BOOL IsInUp(POINT* p);
//	virtual BOOL IsInDown(POINT* p);
//	virtual BOOL IsInBar(POINT* p);
//	virtual INT MakeInRange(INT pos);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, UINT range = 100, UINT step = 1, DLGMSGFUNC onPosChange = nullptr);
//	virtual BOOL CreateInner(UDialog* pDialog, UItem* parent, URect* rc, UINT range = 100, UINT step = 1, DLGMSGFUNC onPosChange = nullptr);
//	virtual BOOL Show();
//	virtual BOOL Up();
//	virtual BOOL Down();
//
//	//Display
//protected:
//	virtual BOOL ShowUp(COLORREF rect, COLORREF text);
//	virtual BOOL ShowDown(COLORREF rect, COLORREF text);
//	virtual BOOL ShowUpDown(COLORREF rect, COLORREF text);
//	virtual BOOL ShowBar(COLORREF rect);
//	virtual BOOL ShowRect();
//
//	//Callbacks
//public:
//	DLGMSGFUNC m_onPosChange;
//
//	//Messages
//public:
//	virtual BOOL OnLClick();
//};
//
//class UComboBox :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UComboBox() {
//		m_type = ComboBox;
//	}
//};
//
//class UListBox :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UListBox() {
//		m_type = ListBox;
//		m_sel = -1;
//		m_onSelChange = nullptr;
//	}
//
//	//Data
//protected:
//	std::vector <STRING>m_data;
//	UINT m_sel;
//	UVScrollBar m_scroll;
//public:
//	virtual BOOL Add(STRING text);
//	virtual BOOL Delete(INT nIndex);
//	virtual INT Insert(INT nIndex, STRING text);
//	virtual BOOL Empty();
//	virtual BOOL SetString(INT nIndex, STRING text);
//	virtual STRING GetString(INT nIndex);
//	virtual INT Find(STRING text, INT nStart = 0);
//	virtual BOOL SetSelect(UINT nSel);
//	virtual INT GetSelect();
//protected:
//	virtual BOOL UpdateScroll();
//	virtual BOOL GetStringRect(URect* rc, UINT n);
//	virtual BOOL IsInScroll(POINT* p);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, DLGMSGFUNC onSelChange = nullptr);
//	virtual BOOL Show();
//	virtual BOOL SetShowMode(UITEMSTATE showmode = UWS_FORMAL);
//	virtual BOOL Update();
//
//	//Callbacks
//protected:
//	DLGMSGFUNC m_onSelChange;
//
//	//Display
//protected:
//	virtual BOOL ShowBackGround(COLORREF pen, COLORREF brush);
//
//	//Messages
//public:
//	static BOOL OnSelChange(UDialog* dlg, UItem* item);
//	virtual BOOL OnMouse();
//	virtual BOOL OnLClick();
//	virtual BOOL OnDisable();
//};
//
//class USliderControl :
//	public UItem {
//	//Constructors
//public:
//	INLINE USliderControl() {
//		m_type = SliderControl;
//		m_min = 0;
//		m_max = 100;
//		m_step = 1;
//		m_pos = 0;
//		m_filled = FALSE;
//		m_onPosChange = nullptr;
//		m_tick.clear();
//	}
//
//	//Data
//protected:
//	UINT m_pos;
//	std::vector<UINT>m_tick;
//public:
//	virtual BOOL SetPos(UINT pos);
//	virtual UINT GetPos();
//	virtual BOOL SetTick(UINT pos);
//	virtual BOOL SetTickFreq(UINT freq);
//	virtual BOOL GetTick(std::vector<UINT>* tick);
//
//	//Attributes
//protected:
//	UINT m_min, m_max;
//	UINT m_step;
//	BOOL m_filled;
//public:
//	virtual BOOL SetRange(UINT min, UINT max);
//	virtual BOOL GetRange(UINT* min, UINT* max);
//protected:
//	virtual BOOL GetBarRect(URect* rc);
//	virtual BOOL GetChannelRect(URect* rc);
//	virtual BOOL GetFilledRect(URect* rc);
//	virtual BOOL IsInBar(POINT* p);
//	virtual BOOL IsInChannel(POINT* p);
//	virtual INT PosToPoint(UINT pos);
//	virtual UINT PointToPos(INT point);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, UINT min = 0, UINT max = 100, BOOL filled = FALSE, DLGMSGFUNC onPosChange = nullptr);
//	virtual BOOL Show();
//
//	//Callbacks
//protected:
//	DLGMSGFUNC m_onPosChange;
//
//	//Display
//protected:
//	virtual BOOL ShowBackGround();
//	virtual BOOL ShowTick();
//	virtual BOOL ShowChannel(COLORREF pen, COLORREF brush, COLORREF fill);
//	virtual BOOL ShowBar(COLORREF pen, COLORREF brush);
//
//	//Messages
//public:
//	virtual BOOL OnLClick();
//};
//
//class UStaticLine :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UStaticLine() {
//		m_type = StaticLine;
//		m_lineWidth = 1;
//	}
//
//	//Attributes
//protected:
//	USHORT m_lineWidth;
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, INT lineWidth = 1);
//	virtual BOOL Show();
//};
//
//class UStaticRect :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UStaticRect() {
//		m_type = StaticRect;
//		m_edgeWidth = 1;
//	}
//
//	//Attributes
//protected:
//	USHORT m_edgeWidth;
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, INT edgeWidth = 1, DLGMSGFUNC onLClick = nullptr, DLGMSGFUNC onRClick = nullptr);
//	virtual BOOL Show();
//
//	//Callbacks
//protected:
//	DLGMSGFUNC m_onLClick = nullptr;
//	DLGMSGFUNC m_onRClick = nullptr;
//
//	//Messages
//public:
//	virtual BOOL OnLClick();
//	virtual BOOL OnRClick();
//};
//
//
//class UNumEdit :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UNumEdit() {
//		m_type = NumEdit;
//		m_isFloat = FALSE;
//		m_max = 10;
//		m_num.i = 0;
//		m_curState = FALSE;
//	}
//
//	//Data
//protected:
//	BOOL m_isFloat;
//	union {
//		unsigned long long int i;
//		long double f;
//	}m_num;
//	BOOL m_curState;
//protected:
//	STRING GetNumString();
//
//	//Attributes
//protected:
//	INT m_max;
//public:
//	BOOL SetMax(INT max);
//	INT GetMax();
//protected:
//	BOOL GetNumRect(URect* rcNum);
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc, FLOAT num = 0, BOOL isFloat = FALSE, INT max = 10, DLGMSGFUNC onNumChange = nullptr);
//	virtual BOOL Show();
//
//	//Callbacks
//protected:
//	DLGMSGFUNC m_onNumChange = nullptr;
//
//	//Messages
//public:
//	virtual BOOL OnMouse();
//	virtual BOOL OnMouseLeave();
//	virtual BOOL OnLClick();
//	virtual VOID OnKey(KEY_EVENT_RECORD* k);
//};
//
//class UTest :
//	public UItem
//{
//	//Constructors
//public:
//	INLINE UTest() {
//		m_type = Default;
//	}
//
//
//	//Operations
//public:
//	virtual BOOL Create(UDialog* pDialog, URect* rc);
//
//	virtual VOID OnKey(KEY_EVENT_RECORD* k);
//};

#endif //UITEM_H
