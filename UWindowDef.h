#pragma once

#ifndef UWINDOWDEF_H
#define UWINDOWDEF_H


#include <windows.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
//namespace Gdiplus {};
//using namespace Gdiplus;
//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib") 

//#define sprintf_s sprintf
//#define max(a,b) a>b?a:b

#define MSG_TIME	0
#define INLINE inline
//#define _DEBUG
////////////////////////////////////////////////////////////////////////////////
//
// Structures
//

//Pre-definition

class UWidget;
class UDialog;
class UItem;
class UMenu;
class UTaskBar;
class UWindow;
class UPaint;

#ifdef UNICODE
# define STRING	std::wstring
# define _T(s)	L##s
#else
# define STRING std::string
# define _T(s)	s
#endif

enum ITEMTYPE {
	Default,
	Button,
	CheckBox,
	StaticLine,
	HScrollBar,
	VScrollBar,
	ComboBox,
	ProgressBar,
	ListBox,
	SliderControl,
	StaticText,
	StaticRect,
	NumEdit,
};
//
//enum UITEMSTATE {
//	UWS_HIDE,
//	UWS_FORMAL,
//	UWS_FOCUS,
//	UWS_TARGET,
//	UWS_CLICK,
//	UWS_DISABLE,
//	UWS_ERROR,
//	UWS_PAUSE
//};
//
//#define UWS_HIDE 0x00000001U
//static CONST UINT UWS_DISABLE = 0x00000002U;sr
//static CONST UINT UWS_SMASK = 0x00001111U;
//static CONST UINT UWS_FOCUS = 0x00011111U;
//static CONST UINT UWS_TARGET = 0x00021111U;
//static CONST UINT UWS_CLICK = 0x00031111U;
//static CONST UINT UWS_ERROR = 0x00041111U;
//static CONST UINT UWS_PAUSE = 0x00051111U;

static CONST BYTE UWS_FORMAL = 0x00;
static CONST BYTE UWS_HIDE = 0x01;
static CONST BYTE UWS_DISABLE = 0x02;
static CONST BYTE UWS_TARGET = 0x04;
static CONST BYTE UWS_SMASK = 0x0F;
static CONST BYTE UWS_FOCUS = 0x10;
static CONST BYTE UWS_CLICK = 0x20;
static CONST BYTE UWS_ERROR = 0x30;
static CONST BYTE UWS_PAUSE = 0x40;

class UItemState {
	//Constructure
public:
	INLINE UItemState() {
		m_state = 0x00;
	}

	//Data
protected:
	BYTE m_state;

public:
	INLINE BYTE GetState() {
		return m_state & 0x0F;
	}
	INLINE BYTE GetShow() {
		return m_state & 0xF0;
	}
	INLINE BOOL IsShow() {
		return !(m_state & UWS_HIDE);
	}
	INLINE BOOL IsEnable() {
		return !((m_state & UWS_DISABLE) | (m_state & UWS_HIDE));
	}
	INLINE BOOL Hide() {
		m_state |= UWS_HIDE;
		return TRUE;
	}
	INLINE BOOL Show() {
		m_state &= ~UWS_HIDE;
		return TRUE;
	}
	INLINE BOOL Disable() {
		m_state |= UWS_HIDE;
		return TRUE;
	}
	INLINE BOOL Enable() {
		m_state &= ~UWS_HIDE;
		return TRUE;
	}
	INLINE BOOL Target() {
		m_state |= UWS_TARGET;
		return TRUE;
	}
	INLINE BOOL NoTarget() {
		m_state &= ~UWS_TARGET;
		return TRUE;
	}
	INLINE BOOL Focus() {
		m_state &= UWS_SMASK;
		m_state |= UWS_FOCUS;
		return TRUE;
	}
	INLINE BOOL Click() {
		m_state &= UWS_SMASK;
		m_state |= UWS_CLICK;
		return TRUE;
	}
	INLINE BOOL Error() {
		m_state &= UWS_SMASK;
		m_state |= UWS_ERROR;
		return TRUE;
	}
	INLINE BOOL Pause() {
		m_state &= UWS_SMASK;
		m_state |= UWS_PAUSE;
		return TRUE;
	}
	INLINE BOOL Formal() {
		m_state &= UWS_SMASK;
		return TRUE;
	}
};

enum UMENUSTATE {
	UMS_FORMAL,
	UMS_DISABLE,
	UMS_CLICK,
	UMS_FOCUS,
};

typedef BOOL(*DLGMSGFUNC)(UWidget*, UItem*);
typedef BOOL(*MENUMSGFUNC)(UMenu*);
typedef BOOL(*WNDMSGFUNC)();

#define DEF_DLGMSGFUNC(name) BOOL name(UWidget*,UItem*)
#define DEF_MENUMSGFUNC(name) BOOL name(UMenu*)
typedef struct tagURect {
	LONG l = 0;
	LONG t = 0;
	LONG w = 0;
	LONG h = 0;
	INLINE tagURect() = default;
	INLINE tagURect(LONG left, LONG top, LONG width, LONG height)
	{
		l = left;
		t = top;
		w = width;
		h = height;
	}
	INLINE VOID set(LONG left, LONG top, LONG width, LONG height)
	{
		l = left;
		t = top;
		w = width;
		h = height;
	}
	INLINE LONG r() {
		return l + w;
	}
	INLINE LONG b() {
		return t + h;
	}
	INLINE POINT lt() {
		return POINT{ l,t };
	}
	INLINE POINT rt() {
		return POINT{ r(),t };
	}
	INLINE POINT lb() {
		return POINT{ l,b() };
	}
	INLINE POINT rb() {
		return POINT{ r(),b() };
	}
	INLINE BOOL DialogToItem(POINT* p)
	{
		p->x -= l;
		p->y -= t;
		if (p->x < 0 || p->y < 0 || p->x > w || p->y > h) {
			return FALSE;
		}
		return TRUE;
	}
	INLINE BOOL PointInRect(POINT* p) {
		if (l <= p->x) {
			if (p->x <= r()) {
				if (t <= p->y) {
					if (p->y <= b()) {
						return TRUE;
					}
				}
			}
		}
		return FALSE;
	}
	INLINE tagURect operator = (tagURect rc)
	{
		l = rc.l;
		t = rc.t;
		w = rc.w;
		h = rc.h;
		return rc;
	}
	INLINE RECT operator = (RECT rc)
	{
		l = rc.left;
		t = rc.top;
		w = rc.right - rc.left;
		h = rc.bottom - rc.top;
		return rc;
	}
	INLINE operator RECT() {
		return RECT{ l,t,r(),b() };
	}
}URect;

extern UWindow wnd;

////////////////////////////////////////////////////////////////////////////////
//
// Exceptions
//

VOID CheckHandle(HANDLE h, STRING file, UINT line);
VOID CheckValue(INT x, STRING file, UINT line);
VOID CheckValue(LPVOID x, STRING file, UINT line);
VOID CheckEOF(INT x, STRING file, UINT line);
#ifdef _DEBUG
#define CHECKHANDLE(h)	CheckHandle(h,__FILE__,__LINE__)
#define CHECKVALUE(x)	CheckValue(x,__FILE__,__LINE__)
#define CHECKEOF(x)		CheckEOF(x,__FILE__,__LINE__)
#define CHECKTHIS()		CheckValue(this,__FILE__,__LINE__)
#else
#define CHECKHANDLE(h)	(h)
#define CHECKVALUE(x)	(x)
#define CHECKEOF(x)		(x)
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Easy using
//

INT ConMessageBox(STRING text, STRING title = _T(""), UINT mode = MB_OK);


////////////////////////////////////////////////////////////////////////////////
//
// Operation
//

//Don't use ::system() by yourself.
//Because it may make your mouse not work
#define system UDialogSystem
INT UDialogSystem(LPCSTR command);

long double GetScale();


#define WFC_LBUTTON		FROM_LEFT_1ST_BUTTON_PRESSED	//Left button
#define WFC_RBUTTON		RIGHTMOST_BUTTON_PRESSED		//Right button
#define WFC_MBUTTON		FROM_LEFT_2ND_BUTTON_PRESSED	//Middle button
//Waiting until 'dwButton' be clicked
// - dwButton:		WFC_xxx
// - ReturnValue	Place of click





////////////////////////////////////////////////////////////////////////////////
//
// GDI
//



//CB = Color background		CR = Color rect		CT = Color Text		CB = Color Bar	CL = Color line
//BTN = Button		CHB = Check Box		PB = Progress Bar	SB = (H/V)Scroll Bar
//Pen,Brush / Text color

#define CB_WINDOW			RGB(240,240,240)


#define CR_STB_FORMAL		RGB(173,173,173)

#define CT_STB_FORMAL		RGB(0,0,0)


#define CR_BTN_FORMAL		RGB(173,173,173)	,RGB(225,225,225)
#define CR_BTN_FOCUS		RGB(0,120,215)		,RGB(229,241,251)
#define CR_BTN_CLICK		RGB(0,84,153)		,RGB(204,228,247)
#define CR_BTN_DISABLE		RGB(191,191,191)	,RGB(204,204,204)

#define CT_BTN_FORMAL		RGB(0,0,0)
#define CT_BTN_DISABLE		RGB(131,131,131)


#define CR_CHB_FORMAL		RGB(51,51,51)		,RGB(255,255,255)
#define CR_CHB_FOCUS		RGB(0,120,215)		,RGB(255,255,255)
#define CR_CHB_CLICK		RGB(0,84,153)		,RGB(204,228,247)
#define CR_CHB_DISABLE		RGB(204,204,204)	,RGB(255,255,255)

#define CT_CHB_FORMAL		RGB(0,0,0)
#define CT_CHB_DISABLE		RGB(109,109,109)


#define CR_PB_FORMAL		RGB(188,188,188)	,RGB(230,230,230)
#define CR_PB_FOCUS			RGB(0,120,215)		,RGB(230,230,230)
#define CR_PB_DISABLE		RGB(191,191,191)	,RGB(230,230,230)
#define CR_PB_ERROR			RGB(191,191,191)	,RGB(230,230,230)
#define CR_PB_PAUSE			RGB(191,191,191)	,RGB(230,230,230)

#define CB_PB_FORMAL		RGB(188,188,188)	,RGB(6,176,37)
#define CB_PB_FOCUS			RGB(0,120,215)		,RGB(64,202,81)
#define CB_PB_DISABLE		RGB(191,191,191)	,RGB(140,140,140)
#define CB_PB_ERROR			RGB(191,191,191)	,RGB(218,38,38)
#define CB_PB_PAUSE			RGB(191,191,191)	,RGB(218,203,38)


#define CR_SB_FORMAL		RGB(240,240,240)

#define CL_SB_FORMAL		RGB(255,255,255)

#define CB_SB_FORMAL		RGB(205,205,205)
#define CB_SB_FOCUS			RGB(192,192,192)
#define CB_SB_FOCUSON		RGB(166,166,166)
#define CB_SB_CLICK			RGB(96,96,96)
#define CB_SB_DISABLE		RGB(240,240,240)

#define CB_SB_UD_FORMAL		RGB(240,240,240)
#define CB_SB_UD_FOCUSON	RGB(218,218,218)
#define CB_SB_UD_CLICK		RGB(96,96,96)
#define CB_SB_UD_DISABLE	RGB(240,240,240)

#define CT_SB_UD_FORMAL		RGB(96,96,96)
#define CT_SB_UD_FOCUSON	RGB(0,0,0)
#define CT_SB_UD_CLICK		RGB(255,255,255)
#define CT_SB_UD_DISABLE	RGB(191,191,191)


#define CL_LB_FORMAL		RGB(255,255,255)

#define CR_LB_FORMAL		RGB(255,255,255)	,RGB(255,255,255)
#define CR_LB_FOCUS			RGB(0,120,215)		,RGB(255,255,255)
#define CR_LB_DISABLE		RGB(130,135,144)	,RGB(255,255,255)

#define CT_LB_FORMAL		RGB(0,0,0)			,RGB(255,255,255)
#define CT_LB_FOCUS			RGB(0,0,0)			,RGB(255,255,255)		,RGB(0,120,215)
#define CT_LB_CLICK			RGB(255,255,255)	,RGB(0,120,215)
#define CT_LB_DISABLE		RGB(109,109,109)	,RGB(255,255,255)
#define CT_LB_SELDISABLE	RGB(109,109,109)	,RGB(0,120,215)


#define CL_SC_TICK_FORMAL	RGB(0,0,0)

#define CR_SC_CHN_FORMAL	RGB(214,214,214)	,RGB(231,234,234)		,RGB(0,122,217)
#define CR_SC_CHN_FOCUS		RGB(0,120,215)		,RGB(231,234,234)		,RGB(0,122,217)
#define CR_SC_CHN_DISABLE	RGB(214,214,214)	,RGB(231,234,234)		,RGB(180,180,180)
#define CR_SC_BAR_FORMAL	RGB(0,122,217)		,RGB(0,122,217)
#define CR_SC_BAR_FOCUS		RGB(0,78,211)		,RGB(0,122,217)
#define CR_SC_BAR_CLICK		RGB(0,78,211)		,RGB(0,78,211)	
#define CR_SC_BAR_DISABLE	RGB(204,204,204)	,RGB(204,204,204)


#define CL_LINE_FORMAL		RGB(173,173,173)
#define CL_LINE_FOCUS		RGB(0,120,215)
#define CL_LINE_DISABLE		RGB(191,191,191)


#define CR_RECT_FORMAL		RGB(173,173,173)	,RGB(255,255,255)
#define CR_RECT_FOCUS		RGB(0,120,215)		,RGB(255,255,255)
#define CR_RECT_DISABLE		RGB(191,191,191)	,RGB(204,204,204)


#define CR_NE_FORMAL		RGB(173,173,173)	,RGB(255,255,255)
#define CR_NE_FOCUS			RGB(0,0,0)			,RGB(255,255,255)
#define CR_NE_CLICK			RGB(0,120,215)		,RGB(255,255,255)
#define CR_NE_TARGET		RGB(0,120,215)		,RGB(255,255,255)
#define CR_NE_DISABLE		RGB(204,204,204)	,RGB(255,255,255)		,RGB(245,245,245)

#define CT_NE_FORMAL		RGB(0,0,0)
#define CT_NE_DISABLE		RGB(109,109,109)


#define CR_M_FORMAL			RGB(204,206,219)	,RGB(246,246,246)
#define CR_MI_FOCUS			RGB(53,148,223)		,RGB(179,215,243)
#define CL_M_FORMAL			RGB(224,227,230)
#define CT_M_FORMAL			RGB(0,0,0)
#define CB_M_C_FORMAL		RGB(0,0,0)			,RGB(144,200,246)
#define CB_M_P_FORMAL		RGB(0,0,0)



INLINE BYTE GetMidByte(BYTE b1, BYTE b2, UINT pos, UINT range = 100) {
	return (b1 < b2) ? (b1 + (BYTE)((b2 - b1) * (float)pos / (float)range)) : (b1 - (BYTE)((b1 - b2) * (float)pos / (float)range));
}

INLINE COLORREF GetMidColor(COLORREF c1, COLORREF c2, UINT pos, UINT range = 100) {
	BYTE r = GetMidByte(GetRValue(c1), GetRValue(c2), pos, range);
	BYTE g = GetMidByte(GetGValue(c1), GetGValue(c2), pos, range);
	BYTE b = GetMidByte(GetBValue(c1), GetBValue(c2), pos, range);
	return RGB(r, g, b);
}


class UPaint
{
	//Constructure
public:
	INLINE UPaint() {

	}
	INLINE ~UPaint() {

	}

	//Operation
public:
	BOOL Attach(HDC hdc);
	BOOL Make(HDC hdc, LONG w = -1, LONG h = -1);
	BOOL Delete();
	INLINE HDC GetDC() {
		return m_hDC;
	}
	INLINE HBITMAP GetBitmap() {
		return m_hBitmap;
	}
	INLINE operator HDC() {
		return GetDC();
	}
	INLINE operator HBITMAP() {
		return GetBitmap();
	}

	//Data
protected:
	HDC m_hDC;
	HBITMAP m_hBitmap;
	HBITMAP m_oldBitmap;
	HPEN m_oldPen;
	HBRUSH m_oldBrush;

	//Draw
public:
	INLINE VOID SetPen(COLORREF color, INT width = 1, INT style = PS_SOLID)
	{
		HPEN hPen = CreatePen(style, width, color);
		CHECKVALUE(hPen);
		HGDIOBJ old = SelectObject(m_hDC, hPen);
		DeleteObject(old);
	}
	INLINE VOID SetNullPen() {
		HGDIOBJ old = SelectObject(m_hDC, GetStockObject(NULL_PEN));
		DeleteObject(old);
	}
	INLINE VOID SetBrush(COLORREF color)
	{
		HBRUSH hBrush = CreateSolidBrush(color);
		CHECKVALUE(hBrush);
		HGDIOBJ old = SelectObject(m_hDC, hBrush);
		DeleteObject(old);
	}
	INLINE VOID SetNullBrush() {
		HGDIOBJ old = SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
		DeleteObject(old);
	}
	INLINE VOID SetColor(COLORREF pen, COLORREF brush)
	{
		SetPen(pen);
		SetBrush(brush);
	}
	INLINE BOOL DrawRect(URect* rc, COLORREF pen, COLORREF brush)
	{
		SetColor(pen, brush);
		return Rectangle(m_hDC, rc->l, rc->t, rc->r(), rc->b());
	}
	INLINE BOOL DrawTransparentRect(URect* rc, COLORREF pen)
	{
		SetPen(pen);
		SetNullBrush();
		return Rectangle(m_hDC, rc->l, rc->t, rc->r(), rc->b());
	}
	INLINE BOOL DrawNoborderRect(URect* rc, COLORREF brush)
	{
		SetNullPen();
		SetBrush(brush);
		return Rectangle(m_hDC, rc->l, rc->t, rc->r(), rc->b());
	}
	INLINE BOOL Draw2BorderRect(URect* rc, COLORREF out, COLORREF in, COLORREF brush) {
		DrawRect(rc, out, brush);
		rc->l++;
		rc->t++;
		rc->w -= 2;
		rc->h -= 2;
		return DrawRect(rc, in, brush);
	}
	INLINE BOOL DrawString(URect* rc, STRING text, COLORREF color, UINT format = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX)
	{
		SetBkMode(m_hDC, TRANSPARENT);
		SetTextColor(m_hDC, color);
		RECT rect = *rc;
		return DrawText(m_hDC, text.c_str(), text.length(), &rect, format);
	}
	INLINE BOOL DrawStringRect(URect* rc, STRING text, COLORREF ctext, COLORREF brush, COLORREF pen, UINT format = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX)
	{
		return DrawRect(rc, pen, brush) && DrawString(rc, text, ctext, format);
	}
	INLINE BOOL DrawStringNoborderRect(URect* rc, STRING text, COLORREF ctext = RGB(0, 0, 0), COLORREF brush = CB_WINDOW, UINT format = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX)
	{
		return DrawNoborderRect(rc, brush) && DrawString(rc, text, ctext, format);
	}
	INLINE BOOL DrawLine(URect* rc, COLORREF color, INT width = 1)
	{
		POINT p;
		SetPen(color, width);
		BOOL bRet = TRUE;
		bRet &= MoveToEx(m_hDC, rc->l, rc->t, &p);
		bRet &= LineTo(m_hDC, rc->r(), rc->b());
		return bRet;
	}
	INLINE BOOL DrawBitmap(URect* rc, HBITMAP bmp)
	{
		HDC dc = CreateCompatibleDC(m_hDC);
		HBITMAP old = (HBITMAP)SelectObject(dc, bmp);
		BOOL bRet = BitBlt(m_hDC, rc->l, rc->t, rc->w, rc->h, dc, 0, 0, SRCCOPY);
		SelectObject(dc, old);
		DeleteDC(dc);
		return bRet;
	}
	INLINE BOOL Bitblt(URect* rc, HDC dc)
	{
		return  BitBlt(m_hDC, rc->l, rc->t, rc->w, rc->h, dc, 0, 0, SRCCOPY);
	}
	INLINE BOOL DrawNoborderTriangle(UINT x1, UINT y1, UINT x2, UINT y2, UINT x3, UINT y3, COLORREF c)
	{
		SetNullPen();
		SetBrush(c);
		POINT p[3] = {
			{(LONG)x1,(LONG)y1},
			{(LONG)x2,(LONG)y2},
			{(LONG)x3,(LONG)y3},
		};
		return Polygon(m_hDC, p, 3);
	}
	INLINE BOOL SetDefaultFont() {
		HFONT f = (HFONT)GetStockObject(SYSTEM_FONT);
		SelectObject(m_hDC, f);
		return TRUE;
	}
};


class UWindow
{
	//Constructure
public:
	INLINE UWindow() {
		m_dlg = nullptr;
		m_rec.EventType = 0;
		m_run = TRUE;
		charHeight = 21;
		charWidth = 7;
		height = 550;
		width = 800;
		hWnd = GetConsoleWindow();
		ScreenPaint.Attach(GetDC(hWnd));
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		hIn = GetStdHandle(STD_INPUT_HANDLE);
		SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_AUTO_POSITION);
		SetConsoleMode(hOut, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
		bSwapButton = ::GetSystemMetrics(SM_SWAPBUTTON);
		scale = GetScale();

		//Set ctrlhander
		SetConsoleCtrlHandler(OnCtrlMsg, TRUE);

		//Hide cursor
		CONSOLE_CURSOR_INFO curInf;
		GetConsoleCursorInfo(hOut, &curInf);
		curInf.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &curInf);
	}

	//Data
protected:
	STRING m_title;
	UDialog* m_dlg;
	INPUT_RECORD m_rec;
	BOOL m_run;
public:
	INT charHeight;
	INT charWidth;
	INT height;
	INT width;
	HWND hWnd;
	long double scale;
	HANDLE hOut;
	HANDLE hIn;
	UPaint ScreenPaint;
	//UTaskBar TaskBar;
	BOOL bSwapButton;
public:
	INLINE UDialog* GetDlg()
	{
		return m_dlg;
	}
	INLINE VOID GetCursorPos(POINT* p)
	{
		::GetCursorPos(p);
		ScreenToClient(wnd.hWnd, p);
		p->x = (LONG)((long double)p->x * wnd.scale);
		p->y = (LONG)((long double)p->y * wnd.scale);
	}
	INLINE BOOL SetCursor(LPCTSTR curName) {
		HCURSOR hcur = LoadCursor(nullptr, curName);
		SetClassLong(hWnd, GCL_HCURSOR, (long)hcur);
		return TRUE;
	}

	//Operation
public:
	BOOL InitWindow(UDialog* dlg, USHORT width, USHORT height, STRING title);
	virtual BOOL BeginMsgLoop();
	virtual BOOL EndMsgLoop();

	//Messages
public:
	static BOOL __stdcall OnCtrlMsg(DWORD CtrlType);


	//Easy using
public:
	INLINE INT MsgBox(STRING text, STRING title = _T(""), UINT mode = MB_OK)
	{
		if (title == _T("")) {
			title = m_title;
		}
		return ::MessageBox(hWnd, text.c_str(), title.c_str(), mode);
	}
};

#endif //UWINDOWDEF_H

