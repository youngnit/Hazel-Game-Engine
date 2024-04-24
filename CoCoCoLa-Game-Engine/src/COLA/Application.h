#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvents.h"
#include "Events/Events.h"

namespace COLA
{
    class COLA_API Application
    {
    public:
        Application();
        virtual ~Application() = 0;
        void Run();
        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_CodeRunning = 1;
    };
    //在客户端定义
    Application* CreateApplication();
    
}