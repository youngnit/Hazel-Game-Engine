#pragma once


#ifdef COLA_PLATFORM_WINDOWS
extern  COLA::Application* COLA::CreateApplication();

int main(int argc, char** argv)
{
    COLA::Log::Init();
    COLA_CORE_WARN("初始化引擎日志");
    COLA_CLIENT_INFO("初始化客户端日志");
    auto app = COLA::CreateApplication();
    app->Run();

    delete app;
}

#endif // COLA_PLATFORM_WINDOWS









