#pragma once

#include "Gonk/Renderer/Framebuffer.h"

namespace Gonk {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:

		OpenGLFramebuffer(const FramebufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColourAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual const FramebufferSpec& GetSpec() const override { return m_Spec; }

		void Invalidate();
	private:
		uint32_t m_RendererID;
		uint32_t m_ColourAttachment, m_DepthAttachment;

		FramebufferSpec m_Spec; 
	};

}