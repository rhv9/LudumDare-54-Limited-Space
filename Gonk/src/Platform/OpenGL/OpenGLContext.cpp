#include "gkpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Gonk {

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         GK_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       GK_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          GK_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: GK_CORE_TRACE(message); return;
		}

		GK_CORE_ASSERT(false, "Unknown severity level!");
	}


	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		GK_CORE_ASSERT(m_WindowHandle, "");
	}

	void Gonk::OpenGLContext::Init()
	{
		GK_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GK_CORE_ASSERT(status, "Failed to initialise Glad!");

		GK_CORE_INFO("OpenGL Info:");
		GK_CORE_INFO("  Vendor {0}", (const char*)glGetString(GL_VENDOR));
		GK_CORE_INFO("  Renderer {0}", (const char*)glGetString(GL_RENDERER));
		GK_CORE_INFO("  Version {0}", (const char*)glGetString(GL_VERSION));

		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		GK_CORE_INFO("  Major Version {0}", versionMajor);
		GK_CORE_INFO("  Minor Version {0}", versionMinor);

		GK_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");

#ifdef GK_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
	}

	void Gonk::OpenGLContext::SwapBuffers()
	{
		GK_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}