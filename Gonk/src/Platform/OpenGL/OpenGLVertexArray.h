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

		virtual void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer> indexBuffer) override { m_IndexBuffer = indexBuffer; }

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	};


}