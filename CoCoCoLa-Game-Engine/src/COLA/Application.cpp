#include "clpch.h"
#include "Application.h"

#include "Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace COLA {


    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        COLA_CORE_ASSERT(!s_Instance, "应用程序已经存在!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(COLA_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {

    }
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(COLA_BIND_EVENT_FN(Application::OnWindowClose));

        //COLA_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLay(Layer* layer)
    {
        m_LayerStack.PushOverLay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_CodeRunning = 0;
        return 1;

    }

    void Application::Run()
    {
        glfwSwapInterval(1);
        /*WindowResizeEvent e (m_Window->GetWidth(), m_Window->GetHeight());
        COLA_CLIENT_TRACE(e.ToString());*/
        while (m_CodeRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

}