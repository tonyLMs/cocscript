#pragma once
#include <windows.h>
#include "cocscript.h"

enum window_search_mode {
    INCLUDE_MINIMIZED,
    EXCLUDE_MINIMIZED  //excludeÅÅ³ý
};

bool check_window_valid(HWND window, enum window_search_mode mode);

HWND next_window(HWND window, enum window_search_mode mode);

HWND first_window(enum window_search_mode mode);

QString get_window_title(HWND hwnd);

QString get_window_class(HWND hwnd);