#include "gkpch.h"
#include "Renderer2D.h"

#include "Gonk/Renderer/Shader.h"

namespace Gonk {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		glm::mat4 ViewProjectionMatrix;
	};

	static Renderer2DData s_Data;



	void Gonk::Renderer2D::Init()
	{
		GK_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = Gonk::VertexArray::Create();

		s_Data.QuadVertexBuffer = Gonk::VertexBuffer::Create(s_Data.MaxQuads * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			{ Gonk::ShaderDataType::Float4, "a_Colour" },
			{ Gonk::ShaderDataType::Float2, "a_TexCoord" },
			});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		Gonk::Ref<Gonk::IndexBuffer> quadIndexBuffer = Gonk::IndexBuffer::Create(quadIndices, s_Data.MaxIndices);

		delete[] quadIndices;

		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		s_Data.TextureShader = Gonk::Shader::Create("assets/shaders/TextColShader.glsl");

		// create white texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint8_t pixel[] = { 255, 255, 255, 255 };
		s_Data.WhiteTexture->SetData(&pixel, 1);

	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		GK_PROFILE_FUNCTION();

		s_Data.ViewProjectionMatrix = camera.GetViewProjection();
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjectionMatrix", s_Data.ViewProjectionMatrix);

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		GK_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		GK_PROFILE_FUNCTION();

		RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawQuad(position, size, s_Data.WhiteTexture, colour);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture> texture, const glm::vec4& colour)
	{
		GK_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Colour = colour;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f};
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Colour = colour;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Colour = colour;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Colour = colour;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;


		/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3{position, 0.0f});
		transform = glm::scale(transform, { size, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		texture->Bind();
		s_Data.QuadVertexArray->Bind();
		RendererCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}

	void Renderer2D::Shutdown()
	{
		GK_PROFILE_FUNCTION();
	}

}