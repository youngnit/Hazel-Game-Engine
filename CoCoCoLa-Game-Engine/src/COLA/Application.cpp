#include "clpch.h"
#include "Application.h"

#include "Core.h"
#include "COLA/Input.h"

#include "COLA/Renderer/Renderer.h"

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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);
       
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
        COLA_CLIENT_ERROR(e.ToString());
        return 1;

    }

    void Application::Run()
    {
        glfwSwapInterval(1);
        /*WindowResizeEvent e (m_Window->GetWidth(), m_Window->GetHeight());
        COLA_CLIENT_TRACE(e.ToString());*/
        while (m_CodeRunning)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            //auto pos = Input::GetMousePosition();
            //COLA_CORE_TRACE("{0}, {1}", std::get<0>(pos), std::get<1>(pos));
           
            m_Window->OnUpdate();
                
            
        }
    }

}