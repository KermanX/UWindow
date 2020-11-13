#include "UOperation.h"


UTaskBar::UTaskBar()
{
	m_hImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
	m_pTaskBarlist = nullptr;
	m_hWnd = nullptr;
}

UTaskBar::~UTaskBar()
{
	ImageList_Destroy(m_hImageList);
}

// 关联窗体
void UTaskBar::Attach(HWND _hWnd)
{
	m_hWnd = _hWnd;
	if (nullptr == m_pTaskBarlist)
	{
		CoCreateInstance(
			CLSID_TaskbarList, nullptr, CLSCTX_ALL,
			IID_ITaskbarList3, (void**)&m_pTaskBarlist);
	}
	m_pTaskBarlist->SetProgressState(m_hWnd, TBPF_INDETERMINATE);
}

// 添加按钮
BOOL UTaskBar::AddButton(TASKBARBUTTON* pButtonsInfo)
{
	THUMBBUTTON pThumbButtons[1];

	DWORD dwMask = THB_BITMAP | THB_TOOLTIP | THB_FLAGS;
	ImageList_Add(m_hImageList, pButtonsInfo->hBitmap, nullptr);
	pThumbButtons[0].dwMask = (THUMBBUTTONMASK)dwMask;
	pThumbButtons[0].iId = pButtonsInfo->ID;
	pThumbButtons[0].iBitmap = 0;
	memset(pThumbButtons[0].szTip, 0, sizeof(wchar_t) * 260);
	RtlCopyMemory(pThumbButtons[0].szTip, pButtonsInfo->szTip, sizeof(wchar_t) * wcslen(pButtonsInfo->szTip));
	pThumbButtons[0].dwFlags = THBF_ENABLED;

	HRESULT hr/* = CoInitialize(nullptr)*/;
	hr = CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pTaskBarlist));
	if (FAILED(hr))
		return FALSE;

	hr = m_pTaskBarlist->ThumbBarSetImageList(m_hWnd, m_hImageList); if (FAILED(hr)) ConMessageBox("RRR");
	hr = m_pTaskBarlist->ThumbBarAddButtons(m_hWnd, 1, pThumbButtons);
	if (FAILED(hr)) ConMessageBox("!");
	return TRUE;
}

// 设置进度
void UTaskBar::SetProgressValue(ULONGLONG ullCompleted, ULONGLONG ullTotal)
{
	m_pTaskBarlist->SetProgressValue(m_hWnd, ullCompleted, ullTotal);
}

// 设置状态
void UTaskBar::SetProgressState(TBPFLAG tbpFlags)
{
	m_pTaskBarlist->SetProgressState(m_hWnd, tbpFlags);
}


//
//
//
//USoftInfo::USoftInfo()
//{
//    struct SoftInfo softinfo;
//    HKEY RootKey;            // 主键
//    LPCSTR lpSubKey;        // 子键名称
//    HKEY hkResult;            // 将要打开键的句柄 
//    HKEY hkRKey;
//    LONG lReturn;            // 记录读取注册表是否成功
//    STRING strBuffer;
//    STRING strMidReg;
//
//    DWORD index = 0;
//    CHAR szKeyName[255] = { 0 };        // 注册表项名称
//    CHAR szBuffer[255] = { 0 };
//    DWORD dwKeyLen = 255;
//    DWORD dwNameLen = 255;
//    DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
//    RootKey = HKEY_LOCAL_MACHINE;
//    lpSubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
//
//    lReturn = RegOpenKeyExA(RootKey, lpSubKey, 0, KEY_ALL_ACCESS, &hkResult);
//
//    if (lReturn == ERROR_SUCCESS)
//    {
//
//        while (ERROR_NO_MORE_ITEMS != RegEnumKeyExA(hkResult, index, szKeyName, &dwKeyLen, 0, nullptr, nullptr, nullptr))
//        {
//            index++;
//            strBuffer = szKeyName;
//            if (!strBuffer.empty())
//            {
//                strMidReg = (STRING)lpSubKey + "\\" + strBuffer;
//
//                if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, strMidReg.c_str(), 0, KEY_ALL_ACCESS, &hkRKey) == ERROR_SUCCESS)
//                {
//                    RegQueryValueExA(hkRKey, "DisplayName", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strSoftName = szBuffer;
//                    dwNameLen = 255;
//                    memset(szBuffer, 0, 255);
//
//                    RegQueryValueExA(hkRKey, "DisplayVersion", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strSoftVersion = szBuffer;
//                    dwNameLen = 255;
//                    memset(szBuffer, 0, 255);
//
//                    RegQueryValueExA(hkRKey, "InstallLocation", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strInstallLocation = szBuffer;
//                    dwNameLen = 255;
//                    memset(szBuffer, 0, 255);
//
//                    RegQueryValueExA(hkRKey, "Publisher", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strPublisher = szBuffer;
//                    dwNameLen = 255;
//
//                    RegQueryValueExA(hkRKey, "InstallLocation", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strMainProPath = szBuffer;
//                    dwNameLen = 255;
//                    memset(szBuffer, 0, 255);
//
//                    RegQueryValueExA(hkRKey, "UninstallString", 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
//                    softinfo.m_strUninstallPth = szBuffer;
//                    dwNameLen = 255;
//                    memset(szBuffer, 0, 255);
//
//                    if (!softinfo.m_strSoftName.empty())
//                    {
//                        if (strBuffer[0] == 'K' && strBuffer[1] == 'B')
//                        {
//                            m_SystemPatchesArr.push_back(softinfo);
//                        }
//                        else
//                        {
//                            m_SoftInfoArr.push_back(softinfo);
//                        }
//                    }
//                }
//
//                dwKeyLen = 255;
//                memset(szKeyName, 0, 255);
//            }
//        }
//        RegCloseKey(hkResult);
//    }
//    else
//    {
//        ::ConMessageBox("打开注册表失败!","ERROR", MB_ICONWARNING);
//    }
//}
//
//std::vector<SoftInfo> USoftInfo::GetSoftInfo(void) const
//{
//    return m_SoftInfoArr;
//}
//
//void USoftInfo::GetSoftName(std::vector<LPCSTR>& lpszSoftName)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        lpszSoftName.push_back(iter->m_strSoftName.c_str());
//    }
//}
//
//void USoftInfo::GetSoftVersion(std::vector<LPCSTR>& lpszSoftVersion)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        if (!(iter->m_strSoftVersion).empty())
//        {
//            lpszSoftVersion.push_back(iter->m_strSoftVersion.c_str());
//        }
//    }
//}
//
//void USoftInfo::GetInstallLocation(std::vector<LPCSTR>& lpszInstallLocation)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        if (!(iter->m_strInstallLocation).empty())
//        {
//            lpszInstallLocation.push_back(iter->m_strInstallLocation.c_str());
//        }
//    }
//}
//
//void USoftInfo::GetPublisher(std::vector<LPCSTR>& lpszPublisher)
//{
//    std::vector<SoftInfo>::iterator iter;
//
//    bool bSign;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        bSign = true;
//
//        // 初步去重复厂商
//        std::vector<LPCSTR>::iterator itr;
//        for (itr = lpszPublisher.begin(); itr != lpszPublisher.end(); itr++)
//        {
//            if (iter->m_strPublisher == (STRING)*itr)
//            {
//                bSign = false;
//            }
//        }
//
//        if (bSign)
//        {
//            lpszPublisher.push_back(iter->m_strPublisher.c_str());
//        }
//    }
//}
//
//void USoftInfo::GetMainProPath(std::vector<LPCSTR>& lpszMainProPath)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        if (!(iter->m_strMainProPath).empty())
//        {
//            lpszMainProPath.push_back(iter->m_strMainProPath.c_str());
//        }
//    }
//}
//
//void USoftInfo::GetUninstallPth(std::vector<LPCSTR>& lpszSoftName)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
//    {
//        if (!(iter->m_strUninstallPth).empty())
//        {
//            lpszSoftName.push_back(iter->m_strUninstallPth.c_str());
//        }
//    }
//}
//
//std::vector<SoftInfo> USoftInfo::GetSystemPatchesInfo(void) const
//{
//    return m_SystemPatchesArr;
//}
//
//void USoftInfo::GetSystemPatchesName(std::vector<LPCSTR>& lpszSoftName)
//{
//    std::vector<SoftInfo>::iterator iter;
//    for (iter = m_SystemPatchesArr.begin(); iter != m_SystemPatchesArr.end(); iter++)
//    {
//        lpszSoftName.push_back(iter->m_strSoftName.c_str());
//    }
//}