#pragma once

#ifdef COLA_PLATFORM_WINDOWS
    #ifdef COLA_BUILD_DLL
        #define COLA_API __declspec(dllexport)
    #else
        #define  COLA_API __declspec(dllimport)
    #endif // COLA_BUILD_DLL
#else
    #error COLA only support windows
#endif