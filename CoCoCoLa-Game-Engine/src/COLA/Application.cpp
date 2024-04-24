#include "clpch.h"
#include "GLFW/glfw3.h"
#include "Application.h"

namespace COLA {
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {

    }
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        COLA_CORE_TRACE("{0}", e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_CodeRunning = 0;
        return 1;

    }

    void Application::Run()
    {
        /*WindowResizeEvent e (m_Window->GetWidth(), m_Window->GetHeight());
        COLA_CLIENT_TRACE(e.ToString());*/
        while (m_CodeRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }
    
}