#include "gkpch.h"

#include "Gonk/Renderer/RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gonk {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}