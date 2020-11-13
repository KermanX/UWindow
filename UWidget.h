#ifndef UWIDGET_H
#define UWIDGET_H
#include "UWindowDef.h"
class UWidget
{
	//Constructure
public:
	INLINE UWidget() {
		m_parent = nullptr;
	}

	//Attributes
protected:
	URect m_rect;
	UWidget* m_parent;
public:
	INLINE URect GetRect() {
		return m_rect;
	}

	//Operation
protected:
	INLINE BOOL CheckLButton() {
		return (::GetAsyncKeyState(wnd.bSwapButton ?
			VK_RBUTTON : VK_LBUTTON) & 0x8000) ? 1 : 0;
	}
	INLINE BOOL CheckRButton() {
		return (::GetAsyncKeyState(wnd.bSwapButton ?
			VK_LBUTTON : VK_RBUTTON) & 0x8000) ? 1 : 0;
	}
	INLINE BOOL CheckMButton() {
		return (GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 1 : 0;
	}

	

	//Messages
public:
	virtual BOOL OnTimer() = 0;
	virtual BOOL OnMouseMove(POINT* p) = 0;
	virtual BOOL OnLDown(POINT* p) = 0;
	virtual BOOL OnLUp(POINT* p) = 0;
	virtual BOOL OnLClick(POINT* p) = 0;
	virtual BOOL OnRDown(POINT* p) = 0;
	virtual BOOL OnRUp(POINT* p) = 0;
	virtual BOOL OnRClick(POINT* p) = 0;
	virtual BOOL OnKey(KEY_EVENT_RECORD* k) = 0;
	virtual BOOL OnWhelled(POINT* p, UINT n) = 0;
	virtual BOOL OnString(STRING* s) = 0;
	virtual BOOL OnShow(UPaint *p) = 0;
};
#endif //UWIDGET_H

