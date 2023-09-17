#pragma once

#include "Gonk/Renderer/Framebuffer.h"

namespace Gonk {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:

		OpenGLFramebuffer(const FramebufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColourAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual const FramebufferSpec& GetSpec() const override { return m_Spec; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColourAttachment = 0, m_DepthAttachment = 0;

		FramebufferSpec m_Spec; 
	};

}