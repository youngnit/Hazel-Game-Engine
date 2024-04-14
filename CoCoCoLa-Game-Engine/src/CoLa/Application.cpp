#include "clpch.h"

#include "Application.h"
#include "Log.h"
#include "CoLa/Events/ApplicationEvents.h"
namespace Cola {
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        WindowResizeEvent e ((unsigned int)1920, (unsigned int)1080);
        COLA_CLIENT_TRACE(e.ToString());
        while (1);
    }
    
}