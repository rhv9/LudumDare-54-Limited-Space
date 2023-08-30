
#include "gkpch.h"
#include "Application.h"

#include "Gonk/Renderer/Renderer.h"

namespace Gonk {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		GK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
		});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;
			
			out vec4 v_Col;

			void main() {
				gl_Position = vec4(a_Pos, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


		/////////////////////////////////////////////////
		///// Blue square
		/////////////////////////////////////////////////
		m_BlueVertexArray.reset(VertexArray::Create());

		float bluevertices[3 * 4] = {
			-0.75f,  0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			-0.75f, -0.75f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> bluevertexBuffer;
		bluevertexBuffer.reset(VertexBuffer::Create(bluevertices, sizeof(bluevertices)));
		bluevertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			});

		m_BlueVertexArray->AddVertexBuffer(bluevertexBuffer);

		unsigned int blueindices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> blueindexBuffer;
		blueindexBuffer.reset(IndexBuffer::Create(blueindices, 6));
		m_BlueVertexArray->SetIndexBuffer(blueindexBuffer);

		std::string bluevertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Pos;
			
			out vec4 v_Col;

			void main() {
				gl_Position = vec4(a_Pos, 1.0);
			}
		)";

		std::string bluefragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
	
			void main() {
				color = vec4(0.2, 0.2, 1.0, 1.0);
			}

		)";

		m_BlueShader.reset(new Shader(bluevertexSrc, bluefragmentSrc));
		
	}	

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Renderer::BeginScene();

			RendererCommand::SetColour({ 1.0f, 0.0f, 1.0f, 1.0f });
			RendererCommand::Clear();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);
			m_BlueShader->Bind();
			Renderer::Submit(m_BlueVertexArray);


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}
}