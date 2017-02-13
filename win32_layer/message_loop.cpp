#include "win32_headers.h"

#include "main_headers.hpp"

#include "app_state.h"

void process_pending_messages()
{
    MSG msg = {};

	// Cannot use GetMessage since it's blocking and we want to refresh the screen ourselves.
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
		switch (msg.message)
		{
            case WM_QUIT:
            {
                app_globals._running = false;
            
                break;
            }

		    case WM_SYSKEYDOWN:
		    case WM_SYSKEYUP:
		    case WM_KEYDOWN:
		    case WM_KEYUP:
		    {
			    WPARAM key_code = msg.wParam;

			    // needs to be set to be boolean so we can compare the values
			    // https://msdn.microsoft.com/en-us/library/windows/desktop/gg153546%28v=vs.85%29.aspx
			    /*One flag that might be useful is bit 30, the "previous key state" flag, which is set to 1 for repeated key-down messages.*/
			    bool key_down      = ((msg.lParam & (1 << 31)) == 0); // sets 31st bit
			    bool prev_key_down = ((msg.lParam & (1 << 30)) != 0); // always 1 for WM_KEYUP

			    bool alt_key_down = ((msg.lParam & (1 << 29)) != 0);

			    // prevent key-repeate messages
			    if (prev_key_down != key_down)
			    {
				    switch (key_code)
				    {
					    case VK_ESCAPE: 
                        {  
                            app_globals._running = false; 
                            break; 
                        }
					    case VK_F4:
					    {
						    // enable ALT + F4

						    if (alt_key_down)
						    {
                                app_globals._running = false; 
						    }

						    break;
					    }
				    }
			    }

			    break;
		    }

		    case WM_MBUTTONDOWN:
		    case WM_MBUTTONUP:
		    {
			    break;
		    }

		    default:
		    {
			    TranslateMessage(&msg);
			    DispatchMessage(&msg);

			    break;
		    }
        }
    }
}
