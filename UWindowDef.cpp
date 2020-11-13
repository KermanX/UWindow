#include "UWindowDef.h"
#include "UOperation.h"
#include "UWindow.h"


UWindow wnd;

VOID CheckHandle(HANDLE h, STRING file, UINT line)
{
	if (h == INVALID_HANDLE_VALUE) {
		ConMessageBox("An ERROR has been happened\n\
-HANDLE ERROR(=INVALID_HANDLE_VALUE)\n\
        FILE:" + file + "\n\
        LINE:" + std::to_string(line), "HANDLE ERROR", MB_OK | MB_ICONERROR);
	}
}
VOID CheckValue(INT x, STRING file, UINT line)
{
	if (x == 0) {
		ConMessageBox("An ERROR has been happened\n\
-VALUE ERROR(=0)\n\
        FILE:" + file + "\n\
        LINE:" + std::to_string(line), "VALUE ERROR", MB_OK | MB_ICONERROR);
	}
}
VOID CheckValue(LPVOID x, STRING file, UINT line)
{
	CheckValue((INT)x, file, line);
}
VOID CheckEOF(INT x, STRING file, UINT line)
{
	if (x == EOF) {
		ConMessageBox("An ERROR has been happened\n\
-VALUE ERROR(=EOF)\n\
        FILE:" + file + "\n\
        LINE:" + std::to_string(line), "VALUE ERROR", MB_OK | MB_ICONERROR);
	}
}



INT ConMessageBox(STRING text, STRING title, UINT mode)
{
	return MessageBoxA(GetConsoleWindow(), text.c_str(), title.c_str(), mode);
}

INT UDialogSystem(LPCSTR command)
{
	FILE* pipe = _popen(command, "r");
	if (!pipe) {
		return FALSE;
	}
	_pclose(pipe);
	return TRUE;
}


long double GetScale()
{
	// 获取窗口当前显示的监视器
	// 使用桌面的句柄.
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度与高度
	MONITORINFOEXA miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfoA(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// 获取监视器物理宽度与高度
	DEVMODEA dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettingsA(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	int cyPhysical = dm.dmPelsHeight;

	// 缩放比例计算  实际上使用任何一个即可
	long double horzScale = ((long double)cxPhysical / (long double)cxLogical);
	long double vertScale = ((long double)cyPhysical / (long double)cyLogical);
	CHECKVALUE(horzScale == vertScale); // 宽或高这个缩放值应该是相等的
	return horzScale;
}



BOOL UWindow::InitWindow(UDialog* dlg, USHORT width, USHORT height, STRING title)
{

	m_dlg = dlg;
	BOOL bRet = TRUE;

	//Set console window size
	COORD pos = { (SHORT)width ,(SHORT)height };
	SMALL_RECT src = { 0 , 0 , width - 1 ,height - 1 };
	bRet &= SetConsoleScreenBufferSize(hOut, pos);
	bRet &= SetConsoleWindowInfo(hOut, true, &src);
	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(hOut, FALSE, &cfi);
	INT x = cfi.dwFontSize.X * width, y = cfi.dwFontSize.Y * height;
	bRet &= SetWindowPos(hWnd, nullptr, 0, 0, x, y, SWP_NOMOVE | SWP_NOREPOSITION);
	width = x;
	height = y;
	m_dlg->SetSize(x, y);
	//Set title
	bRet &= SetConsoleTitleA(title.c_str());

	return bRet;
}

BOOL UWindow::BeginMsgLoop()
{
	FlushConsoleInputBuffer(hIn);

	PAINTSTRUCT ps;
	//hScreenDC = BeginPaint(hWnd, &ps);

	while (m_run) {
		Sleep(MSG_TIME);

		m_dlg->OnTimer();

		m_dlg->OnShow(&ScreenPaint);

		MOUSE_EVENT_RECORD* mrec;
		DWORD dw;

		GetNumberOfConsoleInputEvents(hIn, &dw);
		if (dw == 0)continue;
		ReadConsoleInputA(hIn, &m_rec, 1, &dw);
		if (dw == 0)continue;
		FlushConsoleInputBuffer(hIn);

		POINT p;
		GetCursorPos(&p);

		if (m_rec.EventType == MOUSE_EVENT) {
			mrec = &m_rec.Event.MouseEvent;
			if (mrec->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				m_dlg->OnLDown(&p);
			}
			else {
				if (mrec->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
				{
					m_dlg->OnRDown(&p);
				}
				else {
					m_dlg->OnMouseMove(&p);
				}

			}
			if (mrec->dwEventFlags == MOUSE_WHEELED) {
				m_dlg->OnWhelled(&p, HIWORD(mrec->dwButtonState));
			}
		}
		else if (m_rec.EventType == KEY_EVENT) {
			m_dlg->OnKey(&m_rec.Event.KeyEvent);
		}

		/*
		HPEN hPen = CreatePen(PS_SOLID,5,RGB(255,255,255));
		CHECKVALUE(hPen);
		HGDIOBJ old = SelectObject(hScreenDC, hPen);
		DeleteObject(old);
		MoveToEx(hScreenDC, 0, 0, NULL);
		LineTo(hScreenDC, 100, 100);*/
	}
	EndPaint(hWnd, &ps);

	return TRUE;
}

BOOL UWindow::EndMsgLoop()
{
	m_run = FALSE;
	return TRUE;
}

BOOL __stdcall UWindow::OnCtrlMsg(DWORD CtrlType)
{
	return TRUE;
}

BOOL UPaint::Attach(HDC hdc)
{
	m_hDC = hdc;
	m_hBitmap = (HBITMAP)GetCurrentObject(m_hDC, OBJ_BITMAP);
	m_oldBitmap = m_hBitmap;
	m_oldPen = (HPEN)SelectObject(m_hDC, GetStockObject(NULL_PEN));
	m_oldBrush = (HBRUSH)SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
	return TRUE;
}

BOOL UPaint::Make(HDC hdc, LONG w, LONG h)
{
	if (w == -1 && h == -1) {
		HBITMAP hbmp = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);
		if (!hbmp)
		{
			wnd.MsgBox("!");
		}
		BITMAP bmp;
		GetObject(hbmp, sizeof(bmp), &bmp);
		w = bmp.bmWidth, h = bmp.bmHeight;
	}
	m_hDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, w, h);
	m_oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	m_oldPen = (HPEN)SelectObject(m_hDC, GetStockObject(NULL_PEN));
	m_oldBrush = (HBRUSH)SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
	return TRUE;
}

BOOL UPaint::Delete()
{
	DeleteObject(SelectObject(m_hDC, m_oldPen));
	DeleteObject(SelectObject(m_hDC, m_oldBrush));
	SelectObject(m_hDC, m_oldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hDC);
	return TRUE;
}
