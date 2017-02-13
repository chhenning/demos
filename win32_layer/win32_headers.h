// surpress warnings from external headers
#pragma warning(push, 0) 

    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>

    #ifdef WIN32
        #include <direct.h>
        #define GetCurrentDir _getcwd
    #else
        #include <unistd.h>
        #define GetCurrentDir getcwd
     #endif

#pragma warning(pop)
