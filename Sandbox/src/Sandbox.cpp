#include <Gonk.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Gonk::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-0.9f, 0.9f, 1.6f, -1.6f)
	{

		m_VertexArray.reset(Gonk::VertexArray::Create());

		float vertices[3 * 7] = {
			0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		Gonk::Ref<Gonk::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gonk::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			{Gonk::ShaderDataType::Float4, "a_Color" },
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		Gonk::Ref<Gonk::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gonk::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;
			
			out vec4 v_Col;

			void main() {
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Pos, 1.0);
				v_Col = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
	
			in vec4 v_Col;

			void main() {
				color = vec4(0.8, 0.2, 0.2, 1.0);
				color = v_Col;
			}

		)";

		m_Shader.reset(Gonk::Shader::Create(vertexSrc, fragmentSrc));


		/////////////////////////////////////////////////
		///// Blue square
		/////////////////////////////////////////////////
		m_BlueVertexArray.reset(Gonk::VertexArray::Create());

		float bluevertices[3 * 4] = {
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
		};

		Gonk::Ref<Gonk::VertexBuffer> bluevertexBuffer;
		bluevertexBuffer.reset(Gonk::VertexBuffer::Create(bluevertices, sizeof(bluevertices)));
		bluevertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			});

		m_BlueVertexArray->AddVertexBuffer(bluevertexBuffer);

		unsigned int blueindices[] = { 0, 1, 2, 2, 3, 0 };
		Gonk::Ref<Gonk::IndexBuffer> blueindexBuffer;
		blueindexBuffer.reset(Gonk::IndexBuffer::Create(blueindices, 6));
		m_BlueVertexArray->SetIndexBuffer(blueindexBuffer);

		std::string bluevertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			
			uniform mat4 u_ViewProjectionMatrix;	
			uniform mat4 u_Transform;	

			out vec4 v_Col;

			void main() {
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Pos, 1.0);
			}
		)";

		std::string bluefragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Col;
	
			void main() {
				color = vec4(u_Col, 1.0);
			}

		)";

		m_BlueShader.reset(Gonk::Shader::Create(bluevertexSrc, bluefragmentSrc));

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::DragFloat("CameraSpeed", &m_CameraSpeed, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Rotation", &m_Rotation, 1.0f, 0.0f, 360.0f);
		ImGui::DragFloat("RotationSpeed", &m_RotationSpeed, 0.1f, 0.0f, 10.0f);
		ImGui::End();

	}

	void OnUpdate(Gonk::Timestep ts) override
	{
		if (Gonk::Input::IsKeyPressed(GK_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts;

		if (Gonk::Input::IsKeyPressed(GK_KEY_LEFT))
			m_Rotation -= m_RotationSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_RIGHT))
			m_Rotation += m_RotationSpeed * ts;

		if (Gonk::Input::IsKeyPressed(GK_KEY_I))
			m_SquarePosition.y += m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_K))
			m_SquarePosition.y -= m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_L))
			m_SquarePosition.x += m_CameraSpeed * ts;
		if (Gonk::Input::IsKeyPressed(GK_KEY_J))
			m_SquarePosition.x -= m_CameraSpeed * ts;


		Gonk::RendererCommand::SetColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Gonk::RendererCommand::Clear();

		m_Camera.SetPosition(-m_CameraPosition);
		m_Camera.SetRotation(m_Rotation);

		Gonk::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::vec3 whiteCol{0.8f};
		glm::vec3 redCol{0.8f, 0.2f, 0.2f};

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 offset{x * 0.11f, y * 0.11f, 0.0f};
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), offset + m_SquarePosition) * scale;
				
				if ((x + y) % 2 == 0)
					std::dynamic_pointer_cast<Gonk::OpenGLShader>(m_BlueShader)->UniformFloat3("u_Col", redCol);
				else
					std::dynamic_pointer_cast<Gonk::OpenGLShader>(m_BlueShader)->UniformFloat3("u_Col", whiteCol);
					
				m_BlueShader->Bind();
				Gonk::Renderer::Submit(m_BlueShader, m_BlueVertexArray, transform);

			}

		}

		m_Shader->Bind();
		Gonk::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnEvent(Gonk::Event& event)
	{
	}

private:
	Gonk::Ref<Gonk::Shader> m_Shader;
	Gonk::Ref<Gonk::VertexArray> m_VertexArray;

	Gonk::Ref<Gonk::Shader> m_BlueShader;
	Gonk::Ref<Gonk::VertexArray> m_BlueVertexArray;

	Gonk::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition {0.0f};
	float m_CameraSpeed = 1.0f;

	float m_Rotation = 0.0f;
	float m_RotationSpeed = 360.0f;

	glm::vec3 m_SquarePosition{0.0f};
};


class Sandbox : public Gonk::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Gonk::Application* Gonk::CreateApplication() 
{
	return new Sandbox();
}

