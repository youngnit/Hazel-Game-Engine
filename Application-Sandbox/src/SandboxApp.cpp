#include "clpch.h"
#include "imgui/imgui.h"
#include <Cola.h>

class ExampleLayer : public COLA::Layer
{
public:
    ExampleLayer()
        : Layer("示例层")
    {
    }

    void OnUpdate() override
    {
        //COLA_CLIENT_INFO("示例层::更新");
    }

    void OnEvent(COLA::Event& event) override
    {
        //COLA_CLIENT_TRACE("{0}", event.ToString());
        /*if (event.GetEventType() == COLA::EventType::KeyPressed)
        {
            COLA::KeyPressedEvent& e = (COLA::KeyPressedEvent&)event;

            COLA_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
        }*/
    }
    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }

};

class Sandbox : public COLA::Application
{
public:
    Sandbox() 
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {

    }
};

COLA::Application* COLA::CreateApplication()
{
    return new Sandbox();
}