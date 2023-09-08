#include <Gonk.h>

#include <imgui/imgui.h>

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

		std::shared_ptr<Gonk::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gonk::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			{Gonk::ShaderDataType::Float4, "a_Color" },
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		std::shared_ptr<Gonk::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gonk::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjectionMatrix;
			
			out vec4 v_Col;

			void main() {
				gl_Position = u_ViewProjectionMatrix * vec4(a_Pos, 1.0);
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

		m_Shader.reset(new Gonk::Shader(vertexSrc, fragmentSrc));


		/////////////////////////////////////////////////
		///// Blue square
		/////////////////////////////////////////////////
		m_BlueVertexArray.reset(Gonk::VertexArray::Create());

		float bluevertices[3 * 4] = {
			-0.75f,  0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			-0.75f, -0.75f, 0.0f,
		};

		std::shared_ptr<Gonk::VertexBuffer> bluevertexBuffer;
		bluevertexBuffer.reset(Gonk::VertexBuffer::Create(bluevertices, sizeof(bluevertices)));
		bluevertexBuffer->SetLayout({
			{ Gonk::ShaderDataType::Float3, "a_Position" },
			});

		m_BlueVertexArray->AddVertexBuffer(bluevertexBuffer);

		unsigned int blueindices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Gonk::IndexBuffer> blueindexBuffer;
		blueindexBuffer.reset(Gonk::IndexBuffer::Create(blueindices, 6));
		m_BlueVertexArray->SetIndexBuffer(blueindexBuffer);

		std::string bluevertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			
			uniform mat4 u_ViewProjectionMatrix;		

			out vec4 v_Col;

			void main() {
				gl_Position = u_ViewProjectionMatrix * vec4(a_Pos, 1.0);
			}
		)";

		std::string bluefragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
	
			void main() {
				color = vec4(0.2, 0.2, 1.0, 1.0);
			}

		)";

		m_BlueShader.reset(new Gonk::Shader(bluevertexSrc, bluefragmentSrc));

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::DragFloat("CameraSpeed", &m_CameraSpeed, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Rotation", &m_Rotation, 1.0f, 0.0f, 360.0f);
		ImGui::DragFloat("RotationSpeed", &m_RotationSpeed, 0.1f, 0.0f, 10.0f);

		ImGui::End();

	}

	void OnUpdate() override
	{
		if (Gonk::Input::IsKeyPressed(GK_KEY_W))
			m_CameraPosition.y += m_CameraSpeed;
		if (Gonk::Input::IsKeyPressed(GK_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed;
		if (Gonk::Input::IsKeyPressed(GK_KEY_D))
			m_CameraPosition.x += m_CameraSpeed;
		if (Gonk::Input::IsKeyPressed(GK_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed;

		if (Gonk::Input::IsKeyPressed(GK_KEY_LEFT))
			m_Rotation -= m_RotationSpeed;
		if (Gonk::Input::IsKeyPressed(GK_KEY_RIGHT))
			m_Rotation += m_RotationSpeed;


		Gonk::RendererCommand::SetColour({ 1.0f, 0.0f, 1.0f, 1.0f });
		Gonk::RendererCommand::Clear();

		m_Camera.SetPosition(-m_CameraPosition);
		m_Camera.SetRotation(m_Rotation);

		Gonk::Renderer::BeginScene(m_Camera);

		m_BlueShader->Bind();
		Gonk::Renderer::Submit(m_BlueShader, m_BlueVertexArray);

		m_Shader->Bind();
		Gonk::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnEvent(Gonk::Event& event)
	{
	}

private:
	std::shared_ptr<Gonk::Shader> m_Shader;
	std::shared_ptr<Gonk::VertexArray> m_VertexArray;

	std::shared_ptr<Gonk::Shader> m_BlueShader;
	std::shared_ptr<Gonk::VertexArray> m_BlueVertexArray;

	Gonk::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition {0.0f};
	float m_CameraSpeed = 0.1f;

	float m_Rotation = 0.0f;
	float m_RotationSpeed = 2.0f;
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

