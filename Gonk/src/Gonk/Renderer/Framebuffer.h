#pragma once

namespace Gonk {

	struct FramebufferSpec
	{
		uint32_t Width;
		uint32_t Height;

		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;

		virtual const FramebufferSpec& GetSpec() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpec& spec);
	private:

	};

}
