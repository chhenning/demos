#pragma once

#include "win32_headers.h"


#include "main_headers.hpp"

inline
std::string get_error()
{
    LPSTR error_buffer = nullptr;
        
    auto size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
        , NULL
        , GetLastError()
        , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
        , (LPSTR)& error_buffer
        , 0
        , NULL
        );

    std::string error(error_buffer, size);

    LocalFree(error_buffer);

    return error;
}
