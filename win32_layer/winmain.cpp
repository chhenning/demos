#include "win32_headers.h"

#include "app_state.h"
#include "diagnostics.h"
#include "get_error.h"
#include "offscreen_buffer.h"
#include "windows_dimensions.h"

app_state app_globals;

extern void render();

extern void process_pending_messages();

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM );

int CALLBACK WinMain( HINSTANCE hInstance
                    , HINSTANCE // hPrevInstance
                    , LPSTR     // lpCmdLine
                    , int       // nCmdShow
                    )
{
    HRESULT result = {};

    int Window_Width = 1200;
    int Window_Height = 800;

    char executable_name[MAX_PATH];
	DWORD size_of_file_name = GetModuleFileName(NULL, executable_name, sizeof(executable_name));

    /////////////////
    init_diagnostics();

    /////////////////
	WNDCLASS window_class = {};

    // only one window
    // redraw when window is moving or resized
    // when aspect ration changes we need to redraw
    window_class.style = CS_HREDRAW | CS_VREDRAW;

    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = hInstance;
    window_class.lpszClassName = "Win32_Layer_Class";

    if(RegisterClass(&window_class) == 0)
    {
        OutputDebugString(get_error().c_str());

        return 1;
    }


    app_globals._windows_handle = CreateWindowEx( 
		0 /*WS_EX_TOPMOST | WS_EX_LAYERED*/
        , window_class.lpszClassName
        , "Demo"  
        , WS_OVERLAPPEDWINDOW | WS_VISIBLE
        , CW_USEDEFAULT
        , CW_USEDEFAULT
        , Window_Width
        , Window_Height
        , 0
        , 0
        , hInstance
        , 0 // will send WM_CREATE with value
    );

    if(app_globals._windows_handle == NULL)
    {
        OutputDebugString(get_error().c_str());

        return 1;
    }

	app_globals._device_context = GetDC(app_globals._windows_handle);

	int vertical_refresh_rate = GetDeviceCaps(app_globals._device_context, VREFRESH);
	if (vertical_refresh_rate > 1)
	{
		app_globals._monitor_refresh_rate_hertz = vertical_refresh_rate;
	}

	app_globals._game_update_hertz = app_globals._monitor_refresh_rate_hertz / 2.f;
	app_globals._target_seconds_per_frame = 1.f / app_globals._game_update_hertz;

    int64_t last = get_wall_clock();

    while(app_globals._running)
    {
        // A new frame

        //////////////////////////////
        // Message Loop
        /////////////////////////////
        process_pending_messages();


        //////////////////////////////
        // Render
        /////////////////////////////
        render();

        /////////////////////
        // Frame rate
        /////////////////////////////

        int64_t end = get_wall_clock();
        float seconds_elapsed_for_frame = elapsed_time(last, end);

		if (seconds_elapsed_for_frame < app_globals._target_seconds_per_frame)
		{
			while (seconds_elapsed_for_frame < app_globals._target_seconds_per_frame)
			{
				if (sleep_is_granular)
				{
					DWORD ms = (DWORD)((app_globals._target_seconds_per_frame - seconds_elapsed_for_frame) * 1000.f);
					
					if (ms > 0)
					{
						Sleep(ms);
					}
				}

				seconds_elapsed_for_frame = elapsed_time(last, get_wall_clock());
			}
		}
		else
		{
            // if seconds_elapsed_for_frame is inf make sure init_diagnostics() is called

            // when moving a window we end up here

            //OutputDebugString("Missed frame rate\n");
		}

        // the time to blit below will be part of the next frame's timing
        last = get_wall_clock();

        window_dimensions win_dim(app_globals._windows_handle);

		// device context is allocated before the main loop
		// no need to release the dc
        update_window(app_globals._wob
            , app_globals._device_context
            , win_dim._width
            , win_dim._height
        );

    }

    return result;
}