#include "clpch.h"

#include <Cola.h>

class Sandbox : public COLA::Application
{
public:
    Sandbox() 
    {

    }
    ~Sandbox()
    {

    }
};

COLA::Application* COLA::CreateApplication()
{
    return new Sandbox();
}