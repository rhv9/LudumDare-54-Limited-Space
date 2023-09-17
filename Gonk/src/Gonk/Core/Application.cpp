
#include "gkpch.h"
#include "Application.h"

#include "Gonk/Core/Platform.h"
#include "Gonk/Renderer/Renderer.h"

#include "Gonk/Input/KeyCodes.h"

namespace Gonk {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{ 
		GK_PROFILE_FUNCTION();

		GK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(std::bind(&Gonk::Application::OnEvent, this, std::placeholders::_1));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}	

	Application::~Application()
	{
		GK_PROFILE_FUNCTION();

		Renderer::Shutdown();
		GetWindow().Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		GK_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		GK_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Shutdown()
	{
		GK_PROFILE_FUNCTION();

		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		GK_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		// TODO: Temporary
		dispatcher.Dispatch<Gonk::KeyPressedEvent>([](Gonk::KeyPressedEvent& e) {
			if (e.GetKeyCode() == Key::ESCAPE)
				Gonk::Application::Get().Close();
			return false;
		});

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			if (e.Handled)
				break;
			(*--it)->OnEvent(e);
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GK_PROFILE_FUNCTION();

		if (e.getHeight() == 0 || e.getWidth() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.getWidth(), e.getHeight());

		return false;
	}

	void Application::Run()
	{
		GK_PROFILE_FUNCTION();

		while (m_Running)
		{
			GK_PROFILE_SCOPE("RunLoop");

			float time = (float)Platform::GetTime();
			Timestep ts = time - m_LastRenderTime;
			m_LastRenderTime = time;

			if (!m_Minimized)
			{
				{
					GK_PROFILE_SCOPE("LayerStack OnUpdates");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(ts);

				}
			}

			m_ImGuiLayer->Begin();
			{
				GK_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}

		GetWindow().Shutdown();
	}
}