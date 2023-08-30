#pragma once

#include "Gonk/Renderer/VertexArray.h"

namespace Gonk {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override { m_IndexBuffer = indexBuffer; }

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};


}