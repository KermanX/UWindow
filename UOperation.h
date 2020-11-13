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
	HIMAGELIST		m_hImageList;					// ��ť��ͼ��
	ITaskbarList3* m_pTaskBarlist;
	HWND			m_hWnd;

public:
	// ��������
	void Attach(HWND _hWnd);

	// ��Ӱ�ť
	BOOL AddButton(TASKBARBUTTON* pButtonsInfo);

	// ���ý���
	void SetProgressValue(ULONGLONG ullCompleted, ULONGLONG ullTotal);

	// ����״̬
	void SetProgressState(TBPFLAG tbpFlags = TBPF_NOPROGRESS);
};
#ifndef STRING
#define STRING std::string
#endif
struct SoftInfo
{
    // �����
    STRING m_strSoftName;
    // ����汾��
    STRING m_strSoftVersion;
    // �����װĿ¼
    STRING m_strInstallLocation;
    // �����������
    STRING m_strPublisher;
    // ��������������·��
    STRING m_strMainProPath;
    // ж��exe��������·��
    STRING m_strUninstallPth;
};
//
//class USoftInfo
//{
//private:
//    // �����Ѱ�װ���������װ��Ϣ
//    std::vector<SoftInfo> m_SoftInfoArr;
//    // ����ϵͳ������Ϣ
//    std::vector<SoftInfo> m_SystemPatchesArr;
//
//public:
//    USoftInfo();
//    ~USoftInfo() {}
//
//    // ��ȡһ���������������װ��Ϣ��Vector
//    std::vector<SoftInfo> GetSoftInfo(void) const;
//    // ��ȡ�����Ѱ�װ���������
//    void GetSoftName(std::vector<LPCSTR>& lpszSoftName);
//    // ��ȡ�����Ѱ�װ��������汾��
//    void GetSoftVersion(std::vector<LPCSTR>& lpszSoftVersion);
//    // ��ȡ�����Ѱ�װ���������װĿ¼
//    void GetInstallLocation(std::vector<LPCSTR>& lpszInstallLocation);
//    // ��ȡ�����Ѱ�װ���������������
//    void GetPublisher(std::vector<LPCSTR>& lpszPublisher);
//    // ��ȡ�����Ѱ�װ�����������������·��
//    void GetMainProPath(std::vector<LPCSTR>& lpszMainProPath);
//    // ��ȡ�����Ѱ�װ�������ж�س�������·��
//    void GetUninstallPth(std::vector<LPCSTR>& lpszSoftName);
//
//    // ��ȡһ������ϵͳ������Ϣ��Vector
//    std::vector<SoftInfo> GetSystemPatchesInfo(void) const;
//    // ��ȡ�����Ѱ�װϵͳ������
//    void GetSystemPatchesName(std::vector<LPCSTR>& lpszSoftName);
//};

#endif //UOPERATION_H