#include "gkpch.h"
#include "Renderer2D.h"

#include "Gonk/Renderer/Shader.h"

namespace Gonk {

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> QuadShader;
		Ref<Texture> WhiteTexture;

		glm::mat4 ViewProjectionMatrix;
	};

	static Renderer2DData* s_Data;

	void Gonk::Renderer2D::Init()
	{
		GK_PROFILE_FUNCTION();

		s_Data = new Renderer2DData();

		s_Data->QuadVertexArray = Gonk::VertexArray::Create();

		float vertices[] = {
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		};

		Gonk::Ref<Gonk::VertexBuffer> vertexBuffer;
		vertexBuffer = Gonk::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			{ Gonk::ShaderDataType::Float2, "a_TexCoord" },
			});

		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		Gonk::Ref<Gonk::IndexBuffer> indexBuffer;
		indexBuffer = Gonk::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_Data->QuadShader = Gonk::Shader::Create("assets/shaders/TextColShader.glsl");

		// create white texture
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint8_t pixel[] = { 255, 255, 255, 255 };
		s_Data->WhiteTexture->SetData(&pixel, 1);

	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		GK_PROFILE_FUNCTION();

		s_Data->ViewProjectionMatrix = camera.GetViewProjection();
		s_Data->QuadShader->Bind();
		s_Data->QuadShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::EndScene()
	{
		GK_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawQuad(position, size, s_Data->WhiteTexture, colour);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture)
	{
		DrawQuad(position, size, texture, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture> texture, const glm::vec4& colour)
	{
		GK_PROFILE_FUNCTION();

		s_Data->QuadVertexArray->Bind();

		s_Data->QuadShader->SetMat4("u_ViewProjectionMatrix", s_Data->ViewProjectionMatrix);
		s_Data->QuadShader->SetFloat4("u_Col", colour);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3{position, 0.0f});
		transform = glm::scale(transform, { size, 1.0f });
		s_Data->QuadShader->SetMat4("u_Transform", transform);

		texture->Bind();

		RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::Shutdown()
	{
		GK_PROFILE_FUNCTION();

		delete s_Data;
	}

}