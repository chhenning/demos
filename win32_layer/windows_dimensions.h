#pragma once

#include "win32_headers.h"


struct window_dimensions
{
    window_dimensions(HWND handle)
    {
        RECT rect = {};
        GetClientRect(handle, &rect);
        _width = rect.right - rect.left;
        _height = rect.bottom - rect.top;
    }

    int _width;
    int _height;
};
