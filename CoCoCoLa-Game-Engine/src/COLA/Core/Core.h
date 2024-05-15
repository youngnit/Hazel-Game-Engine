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

#ifdef COLA_DEBUG
    #define COLA_ENABLE_ASSERTS
#endif // COLA_DEBUG


#ifdef COLA_ENABLE_ASSERTS
#define COLA_CLIENT_ASSERT(x, ...) { if(!(x)) { COLA_CLIENT_ERROR("断言失败: {0}", __VA_ARGS__); __debugbreak(); } }
#define COLA_CORE_ASSERT(x, ...) { if(!(x)) { COLA_CORE_ERROR("断言失败: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define COLA_CLIENT_ASSERT(x, ...)
#define COLA_CORE_ASSERT(x, ...)
#endif

#define COLA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace COLA {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}