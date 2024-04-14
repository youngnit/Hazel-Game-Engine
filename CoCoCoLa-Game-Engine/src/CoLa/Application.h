#pragma once

#include "Core.h"

namespace Cola
{
    class COLA_API Application
    {
    public:
        Application();
        virtual ~Application() = 0;
        void Run();
        
    };
    //在客户端定义
    Application* CreateApplication();
    
}