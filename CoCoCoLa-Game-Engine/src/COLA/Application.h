#pragma once

#include "COLA/Core.h"
#include "COLA/Window.h"
#include "COLA/Events/ApplicationEvents.h"
#include "COLA/Events/Events.h"
#include "COLA/LayerStack.h"

namespace COLA
{
    class COLA_API Application
    {
    public:
        Application();
        virtual ~Application() = 0;
        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_CodeRunning = 1;
        LayerStack m_LayerStack;
        static Application* s_Instance;
    };
    //在客户端定义
    Application* CreateApplication();
    
}