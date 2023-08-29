
#include "gkpch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

namespace Gonk {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

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

	Application::Application() 
	{
		GK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};


		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->SetLayout(layout);

		int index = 0;
		for (auto& element : m_VertexBuffer->GetLayout())
		{
			GK_TRACE("{0}", element.GetComponentCount());
			GK_TRACE("{0}", ShaderDataTypeToOpenGLBaseType(element.Type));
			GK_TRACE("{0}", element.Normalized);
			GK_TRACE("{0}", m_VertexBuffer->GetLayout().GetStride());
			GK_TRACE("{0}", element.Offset);
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				m_VertexBuffer->GetLayout().GetStride(), 
				(void*)element.Offset);
			index++;
		}

		unsigned int indices[] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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