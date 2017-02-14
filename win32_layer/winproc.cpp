#include "win32_headers.h"

#include "main_headers.hpp"

#include "app_state.h"
#include "get_error.h"
#include "offscreen_buffer.h"
#include "windows_dimensions.h"

LRESULT CALLBACK WindowProc(HWND hwnd
    , UINT msg
    , WPARAM wparam
    , LPARAM lparam)
{
    LRESULT result = {};

    switch (msg)
    {
        case WM_SIZE:
        {
            OutputDebugString("WM_SIZE\n");
            
            window_dimensions win_dim(hwnd);
            resize(app_globals._wob, win_dim._width, win_dim._height);

            
            break;
        }

        case WM_DESTROY:
        {
            OutputDebugString("WM_DESTROY\n");

            app_globals._running = false;

            break;
        }

        case WM_CLOSE:
        {
            OutputDebugString("WM_CLOSE\n");

            app_globals._running = false;

            break;
        }

        case WM_ACTIVATEAPP:
        {
			OutputDebugString("WM_ACTIVATEAPP\n");

            break;
        }

        case WM_PAINT:
        {
            // windows asks us to validate the dirty section which is done by EndPaint().

            OutputDebugString("WM_PAINT\n");

            PAINTSTRUCT ps = {};

            auto device_context = BeginPaint(hwnd, &ps);

            if(device_context == 0)
            {
                OutputDebugString(get_error().c_str());

                return result;
            }

            auto width = ps.rcPaint.right - ps.rcPaint.left;
            auto height = ps.rcPaint.bottom - ps.rcPaint.top;


            if(update_window(app_globals._wob, device_context, width, height) == false)
            {
                app_globals._running = false;
            }

            EndPaint(hwnd, &ps);

            break;
        }

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
			// these message are handled inside the message loop

            // this should not happen
            assert(false);
        
            break;
        }   
        
        default:
        {
            //OutputDebugString("\n");

            // use default handler
            result = DefWindowProc(hwnd, msg, wparam, lparam);
            break;
        }
    }


    return result;
}