#pragma once

#include "win32_headers.h"

#include "get_error.h"

struct win32_offscreen_buffer
{
	BITMAPINFO _info = {};
	int* _memory = nullptr;
	int _width = 0;
	int _height = 0;
};

inline
void draw(win32_offscreen_buffer& display_buffer, int x, int top, int bottom, int color)
{
	if (x < 0 || x >= display_buffer._width)
	{
		return;
	}

	if (top < 0)
	{
		top = 0;
	}

	if (bottom > display_buffer._height)
	{
		bottom = display_buffer._height;
	}

	int* pixel = &display_buffer._memory[top * display_buffer._width + x];
	
	for (int y = top; y < bottom; ++y)
	{
		*pixel = color;
		pixel += display_buffer._width;
	}
}

inline
bool resize(win32_offscreen_buffer& wob, int width, int height)
{
    wob._width = width;
    wob._height = height;

    wob._info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    wob._info.bmiHeader.biWidth = width;
    wob._info.bmiHeader.biHeight= -height; // top down bitmap, origin is top left corner
    wob._info.bmiHeader.biPlanes = 1;
    wob._info.bmiHeader.biBitCount = 32;
    wob._info.bmiHeader.biCompression = BI_RGB;
    wob._info.bmiHeader.biSizeImage = 0;
    wob._info.bmiHeader.biXPelsPerMeter = 0;
    wob._info.bmiHeader.biYPelsPerMeter = 0;
    wob._info.bmiHeader.biClrUsed = 0;
    wob._info.bmiHeader.biClrImportant = 0;

    if(wob._memory!= nullptr)
    {
        delete[] wob._memory;
    }
   
    wob._memory = new int[wob._width * wob._height];
	memset(wob._memory, 0, wob._width * wob._height * 4);


    return true;
}

inline
bool update_window(win32_offscreen_buffer& wob, HDC device_context, int window_width, int window_height)
{
    int offset_x = 10;
    int offset_y = 10;

    // only clear the areas that is not drawn into by the game
	PatBlt(device_context, 0                    , 0                     , window_width, offset_y     , WHITENESS);
    PatBlt(device_context, 0                    , 0                     , offset_x    , window_height, WHITENESS); 
    PatBlt(device_context, 0                    , offset_y + wob._height, window_width, window_height, WHITENESS);
    PatBlt(device_context, offset_x + wob._width, 0                     , window_width, window_height, WHITENESS);


	int scanline_copied = StretchDIBits( device_context
		, offset_x, offset_y, wob._width, wob._height
        ,0, 0, wob._width, wob._height
        ,wob._memory
        ,&wob._info
        ,DIB_RGB_COLORS
        ,SRCCOPY
        );

    if(scanline_copied == 0 && (window_width > 0 || window_height > 0))
    {
        OutputDebugString(get_error().c_str());

        return false;
    }

    return true;
}

