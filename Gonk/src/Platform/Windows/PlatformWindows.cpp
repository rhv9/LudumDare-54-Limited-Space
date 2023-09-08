#include "gkpch.h"

#include "Gonk/Core/Platform.h"

#include <GLFW/glfw3.h>

#ifdef GK_PLATFORM_WINDOWS

namespace Gonk {

	namespace Platform {

		// TODO::TEMP get time should not use glfw, but windows api
		double GetTime()
		{
			return glfwGetTime();
		}

	}
}

#endif