#pragma once


#ifdef COLA_PLATFORM_WINDOWS
extern  Cola::Application* Cola::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Cola::CreateApplication();
    app->Run();

    delete app;
}

#endif // COLA_PLATFORM_WINDOWS
