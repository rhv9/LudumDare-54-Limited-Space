#include "gkpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Gonk {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		GK_CORE_ASSERT(m_WindowHandle, "");
	}

	void Gonk::OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GK_CORE_ASSERT(status, "Failed to initialise Glad!");

		GK_CORE_INFO("OpenGL Info:");
		GK_CORE_INFO("  Vendor {0}", (const char*)glGetString(GL_VENDOR));
		GK_CORE_INFO("  Renderer {0}", (const char*)glGetString(GL_RENDERER));
		GK_CORE_INFO("  Version {0}", (const char*)glGetString(GL_VERSION));
	}

	void Gonk::OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}