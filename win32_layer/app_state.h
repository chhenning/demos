#pragma once

#include "offscreen_buffer.h"


struct app_state
{
    app_state()
    : _running(true)

    , _wob()

    , _monitor_refresh_rate_hertz(60)
    {}

    bool _running;

    HWND _windows_handle;
    HDC _device_context;
    win32_offscreen_buffer _wob;

    int _monitor_refresh_rate_hertz;
    int _vertical_refresh_rate;

    float _game_update_hertz;
    float _target_seconds_per_frame;
};


extern app_state app_globals;
