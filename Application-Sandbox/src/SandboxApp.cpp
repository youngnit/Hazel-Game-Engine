#include <Cola.h>

class Sandbox : public Cola::Application
{
public:
    Sandbox() 
    {

    }
    ~Sandbox()
    {

    }
};

Cola::Application* Cola::CreateApplication()
{
    return new Sandbox();
}

