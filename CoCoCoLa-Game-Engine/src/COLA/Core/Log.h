#pragma once


#include "Core.h"
#include <spdlog/spdlog.h>

namespace COLA {
    class COLA_API Log
    {
    public:
        
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        //引擎
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        //客户端
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

//引擎日志宏
#define COLA_CORE_TRACE(...)    ::COLA::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define COLA_CORE_INFO(...)     ::COLA::Log::GetCoreLogger()->info(__VA_ARGS__)
#define COLA_CORE_WARN(...)     ::COLA::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define COLA_CORE_ERROR(...)    ::COLA::Log::GetCoreLogger()->error(__VA_ARGS__)
#define COLA_CORE_FATAL(...)    ::COLA::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//客户端日志宏
#define COLA_CLIENT_TRACE(...)  ::COLA::Log::GetClientLogger()->trace(__VA_ARGS__)
#define COLA_CLIENT_INFO(...)   ::COLA::Log::GetClientLogger()->info(__VA_ARGS__)
#define COLA_CLIENT_WARN(...)   ::COLA::Log::GetClientLogger()->warn(__VA_ARGS__)
#define COLA_CLIENT_ERROR(...)  ::COLA::Log::GetClientLogger()->error(__VA_ARGS__)
#define COLA_CLIENT_FATAL(...)  ::COLA::Log::GetClientLogger()->fatal(__VA_ARGS__)