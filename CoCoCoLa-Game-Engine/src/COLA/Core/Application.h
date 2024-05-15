#pragma once

#include "COLA/Core/Timestep.h"
#include "COLA/Core/Core.h"
#include "COLA/Core/Window.h"
#include "COLA/Core/LayerStack.h"

#include "COLA/Events/ApplicationEvents.h"
#include "COLA/Events/Events.h"
#include "COLA/ImGui/ImGuiLayer.h"


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
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_CodeRunning = 1;
        LayerStack m_LayerStack;
        static Application* s_Instance;
        float m_LastFrameTime = 0.0f;
        bool m_Minimized = false;
    };
    //在客户端定义
    Application* CreateApplication();
    
}