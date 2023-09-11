#include "gkpch.h"

#include "Gonk/Input/Input.h"
#include "Gonk/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Gonk {


    class WindowsInput : public Input
    {
    protected:
        bool WindowsInput::IsKeyPressedImpl(int keycode)
        {
            GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
            int status = glfwGetKey(window, keycode);
            return status == GLFW_PRESS || status == GLFW_REPEAT;
        }

        bool WindowsInput::IsMouseButtonPressedImpl(int button)
        {
            GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
            int status = glfwGetMouseButton(window, button);
            return status == GLFW_PRESS;
        }

        float WindowsInput::GetMouseXImpl()
        {
            auto [x, y] = GetMousePositionImpl();
            return x;
        }

        float WindowsInput::GetMouseYImpl()
        {
            auto[x, y] = GetMousePositionImpl();
            return y;
        }

        std::pair<float, float> WindowsInput::GetMousePositionImpl()
        {
            GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return std::pair<float, float>((float)xpos, (float)ypos);
        }
    };

    Input* Input::s_Instance = new WindowsInput();

}