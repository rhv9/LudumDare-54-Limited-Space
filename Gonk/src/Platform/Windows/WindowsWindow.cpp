#include "gkpch.h"
#include "WindowsWindow.h"

#include "Gonk/Events/ApplicationEvent.h"
#include "Gonk/Events/KeyEvent.h"
#include "Gonk/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Gonk {

	static bool s_GLFWInitialised = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		GK_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		GK_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		GK_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		GK_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.m_Width = props.Width;
		m_Data.m_Height = props.Height;

		GK_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialised)
		{
			GK_PROFILE_SCOPE("glfwInit");
			// TODO: GLFW terminate in windows shutdown
			int success = glfwInit();
			GK_CORE_ASSERT(success, "Could not initialise GLFW!");
	
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialised = true;
		}
		{
			GK_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.m_Width = width;
				data.m_Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event((Key)key, scancode, 0);
						data.EventCallback(event);
						break;

					}
					case GLFW_RELEASE:
					{	
						KeyReleasedEvent event((Key)key, scancode);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event((Key)key, scancode, 1);
						data.EventCallback(event);
						break;

					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent e(c);
				data.EventCallback(e);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event((MouseButton)button);
						data.EventCallback(event);

						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event((MouseButton)button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

	}

	void WindowsWindow::Shutdown()
	{
		GK_PROFILE_FUNCTION();

		if (m_Shutdown)
			return;

		glfwDestroyWindow(m_Window);
		m_Shutdown = true;
	}

	void WindowsWindow::OnUpdate()
	{
		GK_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		GK_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }
}