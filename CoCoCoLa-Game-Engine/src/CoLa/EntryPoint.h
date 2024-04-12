#pragma once


#ifdef COLA_PLATFORM_WINDOWS
extern  Cola::Application* Cola::CreateApplication();

int main(int argc, char** argv)
{
    Cola::Log::Init();
    COLA_CORE_WARN("初始化引擎日志");
    COLA_CLIENT_INFO("初始化客户端日志");
    auto app = Cola::CreateApplication();
    app->Run();

    delete app;
}

#endif // COLA_PLATFORM_WINDOWS









