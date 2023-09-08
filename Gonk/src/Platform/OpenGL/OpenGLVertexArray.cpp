#include "gkpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Gonk {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Gonk::ShaderDataType::Float:  return GL_FLOAT;
			case Gonk::ShaderDataType::Float2: return GL_FLOAT;
			case Gonk::ShaderDataType::Float3: return GL_FLOAT;
			case Gonk::ShaderDataType::Float4: return GL_FLOAT;
			case Gonk::ShaderDataType::Mat3:   return GL_FLOAT;
			case Gonk::ShaderDataType::Mat4:   return GL_FLOAT;
			case Gonk::ShaderDataType::Int:    return GL_INT;
			case Gonk::ShaderDataType::Int2:   return GL_INT;
			case Gonk::ShaderDataType::Int3:   return GL_INT;
			case Gonk::ShaderDataType::Int4:   return GL_INT;
			case Gonk::ShaderDataType::Bool:   return GL_BOOL;
		}
		GK_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer)
	{
		GK_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() , "Vertex Buffer has no layout");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

}