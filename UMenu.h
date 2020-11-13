#ifndef UMENU_H
#define UMENU_H

#include "UWindowDef.h"
#include "UWidget.h"

#pragma warning(disable:26812)

/* 
 *		+--35--+-----MAX：175-----+-20-+
 *   30 |  √  | ABCDEFG          |  ▶ |
 *      +------+------------------+----+
 *   10         =======================
*/

#define MI_L_HEIGHT		10
#define MI_O_HEIGHT		20
#define MI_LSPACE		2
#define MI_RSPACE		2
#define MI_ICON_LSPACE	2
#define MI_ICON_RSPACE	2
#define MI_ICON_TSPACE	2
#define MI_ICON_BSPACE	2
#define MI_ICON_WIDTH	20
#define MI_MENU_WIDTH	100
#define MI_PULL_WIDTH	15
#define MI_PULL_LSPACE	5
#define MI_PULL_VSPACE	5
#define MI_PULL_RSPACE	5
#define MI_LINE_RSPACE	5
enum MENUITEMTYPE
{
	MIT_NULL,
	MIT_LINE,
	MIT_TEXT,
	MIT_CHECK,
	MIT_PULL
};

class UMenuItem
{
	friend class UMenu;

	//Constructure
public:
	INLINE UMenuItem() {
		m_type = MIT_NULL;
		m_show = UMS_FORMAL;
		m_parent = nullptr;
		m_data = nullptr;
	}
	INLINE UMenuItem(MENUITEMTYPE type,STRING text=_T(""),VOID* data=nullptr){
		Set(type, text, data);
	}

	//Operation
public:
	virtual BOOL Set(MENUITEMTYPE type, STRING text = _T(""), VOID* data = nullptr);
	virtual BOOL Create(UMenu* parent);
	virtual BOOL Disable();
	virtual BOOL Formal();
	
	//Attributes
protected:
	UMenu* m_parent;
	MENUITEMTYPE m_type;
	UMENUSTATE m_show;
	STRING m_text;
	VOID* m_data;
public:
	virtual MENUITEMTYPE GetType();
	virtual BOOL SetShowMode(UMENUSTATE mode);
	virtual UMENUSTATE GetShowMode();
	virtual BOOL SetText(STRING text);
	virtual STRING GetText();
	virtual BOOL SetData(VOID* data);
	virtual VOID* GetData();
	virtual BOOL SetBitmap(HBITMAP bmp);
	virtual HBITMAP GetBitmap();
	virtual BOOL Check();
	virtual BOOL SetCheck(BOOL bChecked);
	virtual BOOL GetCheck();
	virtual UINT GetWidth();
	virtual UINT GetHeight();
};
class UMenu:public UWidget
{
	friend class UMenuItem;

	//Constructure
public:
	INLINE UMenu() {
		m_id = -1;
		m_verticle = TRUE;
		m_p = { 0,0 };
		m_width = MI_MENU_WIDTH;
		m_show = UMS_FORMAL;
		m_dlg = nullptr;
		m_parent = nullptr;
		m_nItems = 0;
		m_lastcall = -1;
	}

	//Attributes
protected:
	UINT m_id;
	BOOL m_verticle;
	UINT m_width;
protected:
	virtual UINT GetID();
	virtual BOOL SetWidth(UINT width);
public:
	virtual UINT GetWidth();

	//Data
protected:
	POINT m_p;
	UMENUSTATE m_show;
	UDialog* m_dlg;
	UMenu* m_parent;
	UINT m_nItems;
	std::vector<UMenuItem> m_pItems;
	UINT m_lastcall;
public:
	virtual UMenu* GetParent();
	virtual UMenuItem* GetChild(UINT n);
protected:
	virtual UINT AddItem(UMenuItem* item);
	virtual UINT AddItem(MENUITEMTYPE type, STRING text, VOID* data);
	virtual UINT AddLine();
	virtual UINT AddText(STRING text, HBITMAP bmp = nullptr);
	virtual UINT AddCheck(STRING text, BOOL bChecked=FALSE);
	virtual UINT AddPull(STRING text, UMenu* menu);
	virtual BOOL ResetWidth();

	//Operation
public:
	virtual BOOL Create(UDialog* dlg, POINT* p);
	virtual BOOL Show();
	virtual BOOL Disable();
	virtual BOOL Formal();
	virtual BOOL Close();

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
};

#endif //UMENU_H
