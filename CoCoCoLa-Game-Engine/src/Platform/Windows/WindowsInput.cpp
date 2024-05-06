#include "clpch.h"

#include "WindowsInput.h"
#include "COLA/Application.h"


#include <GLFW/glfw3.h>

namespace COLA
{
    Input* Input::s_Instance = new WindowsInput;
    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto status = glfwGetKey(window, keycode);

        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }

    bool WindowsInput::IsKMouseButtonImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto status = glfwGetMouseButton(window, button);

        return status == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::pair <float, float>((float)xpos, (float)ypos);
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto x = GetMousePositionImpl();
        return std::get<0>(x);
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto y = GetMousePositionImpl();
        return std::get<1>(y);
    }
}