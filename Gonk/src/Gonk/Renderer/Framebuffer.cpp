#include "gkpch.h"
#include "Framebuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Gonk {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: GK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFramebuffer>(spec);
		}

		GK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}