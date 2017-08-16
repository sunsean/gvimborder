/// :call libcallnr("gvimborder.dll", "SetBorder", 0xFFAA33)

#include <windows.h>

BOOL CALLBACK FindWindowProc(HWND hwnd, LPARAM lParam)
{
  HWND* pphWnd = (HWND*)lParam;

  if (GetParent(hwnd))
  {
    *pphWnd = NULL;
    return TRUE;
  }
  *pphWnd = hwnd;
  return FALSE;
}

BOOL CALLBACK FindChildProc(HWND hwnd, LPARAM lParam)
{
  char lpszClassName[100];

  HWND* pphWnd = (HWND*)lParam;

  GetClassName(hwnd, lpszClassName, 100);
  if ( strcmp(lpszClassName, "VimTextArea") == 0 )
  {
    *pphWnd = hwnd;
    return FALSE;
  }
  return TRUE;
}

LONG __declspec(dllexport) SetBorder(COLORREF backgroundColor)
{
  HWND hTop = NULL;
  HWND hTextArea = NULL;
  DWORD dwThreadID;

  dwThreadID = GetCurrentThreadId();
  EnumThreadWindows(dwThreadID, FindWindowProc, (LPARAM)&hTop);

  if (hTop)
  {
    EnumChildWindows(hTop, FindChildProc, (LPARAM)&hTextArea);

    RECT rc;
    GetWindowRect(hTop, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

    // Remove Borders
    SetWindowLong(hTextArea, GWL_EXSTYLE, GetWindowLong(hTextArea, GWL_STYLE) & ~WS_EX_CLIENTEDGE);
    SetWindowLong(hTextArea, GWL_EXSTYLE, GetWindowLong(hTextArea, GWL_STYLE) & ~WS_EX_WINDOWEDGE);
    SetWindowPos(hTextArea, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);

    // Set Background colors
    HBRUSH b = CreateSolidBrush(backgroundColor);
    SetClassLongPtr(hTop, GCLP_HBRBACKGROUND, (LONG_PTR) b);
    SetClassLongPtr(hTextArea, GCLP_HBRBACKGROUND, (LONG_PTR) b);
  }
  return GetLastError();
}
