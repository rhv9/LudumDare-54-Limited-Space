#include "gkpch.h"
#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

void Sandbox2DLayer::OnAttach()
{
	m_VertexArray = Gonk::VertexArray::Create();

	float vertices[] = {
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	Gonk::Ref<Gonk::VertexBuffer> vertexBuffer;
	vertexBuffer = Gonk::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Gonk::ShaderDataType::Float3, "a_Position" },
		});

	m_VertexArray->AddVertexBuffer(vertexBuffer);

	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
	Gonk::Ref<Gonk::IndexBuffer> indexBuffer;
	indexBuffer = Gonk::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_FlatShader = Gonk::Shader::Create("assets/shaders/FlatColour.glsl");

}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Gonk::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Gonk::RendererCommand::SetColour(glm::vec4{0.2f});
	Gonk::RendererCommand::Clear();

	Gonk::Renderer::BeginScene(m_CameraController.GetCamera());


	m_FlatShader->Bind();
	std::dynamic_pointer_cast<Gonk::OpenGLShader>(m_FlatShader)->UniformFloat4("f_col", m_Col);
	Gonk::Renderer::Submit(m_FlatShader, m_VertexArray, glm::mat4(1.0f));

	Gonk::Renderer::EndScene();
}

void Sandbox2DLayer::OnEvent(Gonk::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Col", &m_Col[0]);
	ImGui::End();
}
