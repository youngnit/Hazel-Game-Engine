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

#define BIT(x) (1 << x)

#ifdef COLA_ENABLE_ASSERTS
#define COLA_CLIENT_ASSERT(x, ...) { if(!(x)) { COLA_CLIENT_ERROR("断言失败: {0}", __VA_ARGS__); __debugbreak(); } }
#define COLA_CORE_ASSERT(x, ...) { if(!(x)) { COLA_CORE_ERROR("断言失败: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define COLA_CLIENT_ASSERT(x, ...)
#define COLA_CORE_ASSERT(x, ...)
#endif