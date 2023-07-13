#include "getscreen.h"

bool check_window_valid(HWND window, enum window_search_mode mode)
{
    DWORD styles, ex_styles;
    RECT  rect;

    if (/*!IsWindowVisible(window) ||*/
        (mode == EXCLUDE_MINIMIZED && IsIconic(window)))
        return false;

    GetClientRect(window, &rect);
    styles = (DWORD)GetWindowLongPtr(window, GWL_STYLE);
    ex_styles = (DWORD)GetWindowLongPtr(window, GWL_EXSTYLE);

    if (ex_styles & WS_EX_TOOLWINDOW)
        return false;
    if (styles & WS_CHILD)
        return false;
    if (mode == EXCLUDE_MINIMIZED && (rect.bottom == 0 || rect.right == 0))
        return false;

    return true;
}

HWND next_window(HWND window, enum window_search_mode mode)
{
    while (true) {
        window = GetNextWindow(window, GW_HWNDNEXT);
        if (!window || check_window_valid(window, mode))
            break;
    }

    return window;
}

HWND first_window(enum window_search_mode mode)
{
    HWND window = GetWindow(GetDesktopWindow(), GW_CHILD);
    if (!check_window_valid(window, mode))
        window = next_window(window, mode);
    return window;
}

QString get_window_title(HWND hwnd)
{
    QString retStr;
    wchar_t* temp;
    int len;

    len = GetWindowTextLengthW(hwnd);
    if (!len)
        return retStr;

    temp = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
    if (GetWindowTextW(hwnd, temp, len + 1))
    {
        retStr = QString::fromWCharArray(temp);
    }
    free(temp);
    return retStr;
}

QString get_window_class(HWND hwnd)
{
    QString retStr;
    wchar_t temp[256];

    temp[0] = 0;
    if (GetClassNameW(hwnd, temp, sizeof(temp) / sizeof(wchar_t)))
    {
        retStr = QString::fromWCharArray(temp);
    }
    return retStr;
}

/*
    HWND pWnd;
    pWnd = first_window(INCLUDE_MINIMIZED); //得到第一个窗口句柄

    qDebug() << get_window_title(pWnd) << "\n";

    pWnd = next_window(pWnd, INCLUDE_MINIMIZED);//得到下一个窗口句柄

    qDebug() << get_window_title(pWnd) << "\n";
*/