//
//
//#include<iostream>
//#include <thread>
#include "UWindow.h"


DEF_DLGMSGFUNC(onc1);

class UMyMenu :public UMenu {
public:
	UMyMenu() {
		AddText("HI");
		AddCheck("CHECK", TRUE);
		AddPull("PULL", nullptr);
	}
};

class UMyDialog :public UDialog {
public:
	UButton btn;
	//UProgressBar pb;
	//URect rc;
	//UStaticLine l;
	//UStaticRect r;
	//UStaticText t;
	//UCheckBox cb;
	//UHScrollBar hsb;
	//UVScrollBar vsb;
	///*UListBox*/USliderControl lb;
	//UTest ts, ts2;
	//UNumEdit ne;
	UMyMenu* menu;
public:
	UMyDialog() :UDialog()
	{
		//URect rc;
		btn.Create(this, &URect{ 0,0,90,60 }, "按钮", onc1);
		//pb.Create(this, &URect{ m_width-151,m_height-156,100,15 },100,3);
		//pb.SetPos(80);
		//r.Create(this, &URect{ 10,10,40,20 });
		//l.Create(this, &URect{ 60,60,100,100 },1);
		//cb.Create(this, &URect{ 140,120,90,10 }, "复选框", 0, 1);
		//hsb.Create(this, &URect{ 50,50,400,20 }, 5, 1);
		//vsb.Create(this, &URect{ 100,90,20,400 }, 5, 1);
		//rc.set( 50,50,500,70 );
		//lb.Create(this, &rc,0,10/*000*/,1,onc1);
		//lb.SetTickFreq(1/*000*/);
		//lb.SetTick(3);
		//t.Create(this, &URect{ 10,10,90,30 }, "文本",0,0);
  //      ts.Create(this, &URect{ 0,0,10,10 });
  //      ts2.Create(this, &URect{ 0,0,10,10 });
		//ne.Create(this, &URect{ 50,50,1000,30 }, 0.0, 1);
	}
	virtual BOOL OnInitDialog() {
		wnd.InitWindow(this,100,30,"Dlg");
		return TRUE;
	}
	virtual BOOL OnRClick(POINT* p) {
		UDialog::OnRClick(p);
		menu = new UMyMenu;
		menu->Create(this, p);
		return TRUE;
	}
	virtual BOOL OnLClick(POINT* p) {
		UDialog::OnLClick(p);
		if (menu != nullptr) {
			menu->Close();
			menu = nullptr;
		}
		return TRUE;
	}/*
	INT nc = 0;
	virtual BOOL OnWhelled(UINT n) {
		UDialog::OnWhelled(n);
		if (n == 65416)nc++;
		if (n == 120) nc--;
		t.SetText(std::to_string(nc));
		return TRUE;
	}*/
};

//
//void f(UMyDialog* dlg) {
//	for (int i = 0; i < 10; i++) {
//		Sleep(1000);
//		dlg->lb.SetPos(i * 1000);
//	}
//}

BOOL onc1(UWidget* dlg, UItem* item) {
	wnd.MsgBox("onc1");
	return TRUE;
}

UINT pos=0;

int main() {
	UMyDialog d;
	d.Run();

	return 1;
}


//
//
//BOOL GetSoftInfo(std::vector<SoftInfo>& v) {
//	struct SoftInfo softinfo;
//	HKEY RootKey;            // 主键
//	LPCSTR lpSubKey;        // 子键名称
//	HKEY hkResult;            // 将要打开键的句柄 
//	HKEY hkRKey;
//	LONG lReturn;            // 记录读取注册表是否成功
//	STRING strBuffer;
//	STRING strMidReg;
//
//	DWORD index = 0;
//	CHAR szKeyName[255] = { 0 };        // 注册表项名称
//	CHAR szBuffer[255] = { 0 };
//	DWORD dwKeyLen = 255;
//	DWORD dwNameLen = 255;
//	DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
//	RootKey = HKEY_LOCAL_MACHINE;
//	lpSubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
//
//	lReturn = RegOpenKeyExA(RootKey, lpSubKey, 0, KEY_ALL_ACCESS, &hkResult);
//
//	if (lReturn == ERROR_SUCCESS)
//	{
//
//		while (ERROR_NO_MORE_ITEMS != RegEnumKeyExA(hkResult, index, szKeyName, &dwKeyLen, 0, nullptr, nullptr, nullptr))
//		{
//			index++;
//			strBuffer = szKeyName;
//			if (!strBuffer.empty())
//			{
//				strMidReg = (STRING)lpSubKey + "\\" + strBuffer;
//
//				if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, strMidReg.c_str(), 0, KEY_ALL_ACCESS, &hkRKey) == ERROR_SUCCESS)
//				{
//					RegQueryValueExA(hkRKey, "DisplayName", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strSoftName = szBuffer;
//					dwNameLen = 255;
//					memset(szBuffer, 0, 255);
//
//					RegQueryValueExA(hkRKey, "DisplayVersion", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strSoftVersion = szBuffer;
//					dwNameLen = 255;
//					memset(szBuffer, 0, 255);
//
//					RegQueryValueExA(hkRKey, "InstallLocation", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strInstallLocation = szBuffer;
//					dwNameLen = 255;
//					memset(szBuffer, 0, 255);
//
//					RegQueryValueExA(hkRKey, "Publisher", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strPublisher = szBuffer;
//					dwNameLen = 255;
//
//					RegQueryValueExA(hkRKey, "InstallLocation", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strMainProPath = szBuffer;
//					dwNameLen = 255;
//					memset(szBuffer, 0, 255);
//
//					RegQueryValueExA(hkRKey, "UninstallString", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//					softinfo.m_strUninstallPth = szBuffer;
//					dwNameLen = 255;
//					memset(szBuffer, 0, 255);
//
//					if (!softinfo.m_strSoftName.empty())
//					{
//						//if (strBuffer[0] == 'K' && strBuffer[1] == 'B')
//					   // {
//						   //m_SystemPatchesArr.push_back(softinfo);
//					   // }
//						//else
//						//{
//						v.push_back(softinfo);
//						//}
//					}
//				}
//
//				dwKeyLen = 255;
//				memset(szKeyName, 0, 255);
//			}
//		}
//		RegCloseKey(hkResult);
//		return TRUE;
//	}
//	else
//	{
//		MessageBoxA(GetConsoleWindow(), "打开注册表失败!", "ERROR", MB_ICONWARNING);
//		return FALSE;
//	}
//}
