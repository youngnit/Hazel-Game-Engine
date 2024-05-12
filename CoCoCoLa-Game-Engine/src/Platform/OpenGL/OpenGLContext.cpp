#include "clpch.h"
#include "OpenGLContext.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace COLA {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        COLA_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        COLA_CORE_ASSERT(status, "初始化GLAD失败!");

        COLA_CORE_INFO("\n-----------------------------------------------------------------------------\nOpenGL 信息");
        COLA_CORE_INFO("显卡供应商:\t{0}", glGetString(GL_VENDOR));
        COLA_CORE_INFO("GPU渲染器:\t{0}", glGetString(GL_RENDERER));
        COLA_CORE_INFO("显卡驱动版本:\t{0}", glGetString(GL_VERSION));
        COLA_CORE_INFO("\n-----------------------------------------------------------------------------");
    }



    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}