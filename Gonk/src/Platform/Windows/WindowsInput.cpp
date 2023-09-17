#include "gkpch.h"

#include "Gonk/Input/Input.h"
#include "Gonk/Core/Application.h"

#include <GLFW/glfw3.h>

#ifdef GK_PLATFORM_WINDOWS

namespace Gonk {

    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
        int status = glfwGetKey(window, keycode);
        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
        int status = glfwGetMouseButton(window, button);
        return status == GLFW_PRESS;
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        auto[x, y] = GetMousePosition();
        return y;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::pair<float, float>((float)xpos, (float)ypos);
    }
}

#endif