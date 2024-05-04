#include "clpch.h"

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
        COLA_CLIENT_INFO("示例层::更新");
    }

    void OnEvent(COLA::Event& event) override
    {
        COLA_CLIENT_TRACE("{0}", event.ToString());
    }

};


class Sandbox : public COLA::Application
{
public:
    Sandbox() 
    {
        PushLayer(new ExampleLayer());
        PushOverLay(new COLA::ImGuiLayer());
    }
    ~Sandbox()
    {

    }
};

COLA::Application* COLA::CreateApplication()
{
    return new Sandbox();
}