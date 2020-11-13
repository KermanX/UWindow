#pragma once

#ifndef UOPERATION_H
#define UOPERATION_H

#include "UWindowDef.h"
#include <Commctrl.h>
#include <Shobjidl.h>
#pragma comment(lib, "Comctl32.lib")
typedef struct tagTASKBARBUTTON {
		HBITMAP		hBitmap;
		const wchar_t* szTip;
		UINT		ID;
		tagTASKBARBUTTON() = default;

	}TASKBARBUTTON;
class UTaskBar
{
	

public:
	UTaskBar();
	~UTaskBar();

private:
	HIMAGELIST		m_hImageList;					// 按钮的图标
	ITaskbarList3* m_pTaskBarlist;
	HWND			m_hWnd;

public:
	// 关联窗体
	void Attach(HWND _hWnd);

	// 添加按钮
	BOOL AddButton(TASKBARBUTTON* pButtonsInfo);

	// 设置进度
	void SetProgressValue(ULONGLONG ullCompleted, ULONGLONG ullTotal);

	// 设置状态
	void SetProgressState(TBPFLAG tbpFlags = TBPF_NOPROGRESS);
};
#ifndef STRING
#define STRING std::string
#endif
struct SoftInfo
{
    // 软件名
    STRING m_strSoftName;
    // 软件版本号
    STRING m_strSoftVersion;
    // 软件安装目录
    STRING m_strInstallLocation;
    // 软件发布厂商
    STRING m_strPublisher;
    // 主程序所在完整路径
    STRING m_strMainProPath;
    // 卸载exe所在完整路径
    STRING m_strUninstallPth;
};
//
//class USoftInfo
//{
//private:
//    // 保存已安装常用软件安装信息
//    std::vector<SoftInfo> m_SoftInfoArr;
//    // 保存系统补丁信息
//    std::vector<SoftInfo> m_SystemPatchesArr;
//
//public:
//    USoftInfo();
//    ~USoftInfo() {}
//
//    // 获取一个包含常用软件安装信息的Vector
//    std::vector<SoftInfo> GetSoftInfo(void) const;
//    // 获取所有已安装常用软件名
//    void GetSoftName(std::vector<LPCSTR>& lpszSoftName);
//    // 获取所有已安装常用软件版本号
//    void GetSoftVersion(std::vector<LPCSTR>& lpszSoftVersion);
//    // 获取所有已安装常用软件安装目录
//    void GetInstallLocation(std::vector<LPCSTR>& lpszInstallLocation);
//    // 获取所有已安装常用软件发布厂商
//    void GetPublisher(std::vector<LPCSTR>& lpszPublisher);
//    // 获取所有已安装常用软件主程序所在路径
//    void GetMainProPath(std::vector<LPCSTR>& lpszMainProPath);
//    // 获取所有已安装常用软件卸载程序所在路径
//    void GetUninstallPth(std::vector<LPCSTR>& lpszSoftName);
//
//    // 获取一个包含系统补丁信息的Vector
//    std::vector<SoftInfo> GetSystemPatchesInfo(void) const;
//    // 获取所有已安装系统补丁名
//    void GetSystemPatchesName(std::vector<LPCSTR>& lpszSoftName);
//};

#endif //UOPERATION_H