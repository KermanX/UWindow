#ifndef UDIALOG_H
#define UDIALOG_H

#include "UWindowDef.h"
#include "UWidget.h"

#pragma warning(disable:26812)

class UDialog : public UWidget {
	friend class UWindow;
	friend class UItem;

	//Constructors
public:
	INLINE UDialog() {
		m_firstItem = nullptr;
		m_keyCall = nullptr;
		m_target = nullptr;
		m_statusText = "Ready";
		m_menu = nullptr;
		m_lastLDown = nullptr;
		m_lastRDown = nullptr;
	}

	virtual ~UDialog() {
	}

	//Data
protected:
	UItem* m_firstItem;
	UItem* m_keyCall;
	UItem* m_target;
	UItem* m_lastLDown;
	UItem* m_lastRDown;
	STRING m_statusText;
	INPUT_RECORD m_rec;
	UMenu* m_menu;
public:
	virtual UItem* AddItem(UItem* pNewItem);
	virtual BOOL SetStatusText(STRING text);
	virtual STRING GetStatusText();
	virtual INPUT_RECORD GetRecord();
	virtual BOOL SetMenu(UMenu* menu);
protected:
	virtual UItem* SetKeyCall(UItem* pItem);
	virtual BOOL SetTarget(UItem* pItem);
	INLINE BOOL SetSize(INT w, INT h) {
		m_rect.w = w;
		m_rect.h = h;
		return TRUE;
	}

	//Operations
public:
	//virtual BOOL Show();
	virtual BOOL Run();
	virtual BOOL End();

	//Display
public:
	virtual BOOL DrawStatusBar();
	virtual BOOL WaitTime();

	//Messages
public:
	virtual BOOL OnCtrlMsg(DWORD CtrlType);
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
	virtual BOOL OnInitDialog();
};





#endif //UDIALOG_H
