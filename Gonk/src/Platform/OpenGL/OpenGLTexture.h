#pragma once
#include "Gonk/Renderer/Texture.h"

#include "glad/glad.h"

namespace Gonk {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(const uint32_t width, uint32_t height);

		virtual ~OpenGLTexture2D() override;
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(const void* data, uint32_t size) const override;
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override 
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;

		GLenum m_InternalFormat, m_DataFormat;
	};

}