#pragma once


#include "Core.h"
#include <spdlog/spdlog.h>
#include <memory>
namespace Cola {
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
#define COLA_CORE_TRACE(...)    ::Cola::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define COLA_CORE_INFO(...)     ::Cola::Log::GetCoreLogger()->info(__VA_ARGS__)
#define COLA_CORE_WARN(...)     ::Cola::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define COLA_CORE_ERROR(...)    ::Cola::Log::GetCoreLogger()->error(__VA_ARGS__)
#define COLA_CORE_FATAL(...)    ::Cola::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//客户端日志宏
#define COLA_CLIENT_TRACE(...)  ::Cola::Log::GetClientLogger()->trace(__VA_ARGS__)
#define COLA_CLIENT_INFO(...)   ::Cola::Log::GetClientLogger()->info(__VA_ARGS__)
#define COLA_CLIENT_WARN(...)   ::Cola::Log::GetClientLogger()->warn(__VA_ARGS__)
#define COLA_CLIENT_ERROR(...)  ::Cola::Log::GetClientLogger()->error(__VA_ARGS__)
#define COLA_CLIENT_FATAL(...)  ::Cola::Log::GetClientLogger()->fatal(__VA_ARGS__)