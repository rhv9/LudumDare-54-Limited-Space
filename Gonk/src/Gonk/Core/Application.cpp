
#include "gkpch.h"
#include "Application.h"

#include "Gonk/Core/Platform.h"
#include "Gonk/Renderer/Renderer.h"

namespace Gonk {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{ 
		GK_PROFILE_FUNCTION();

		GK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Gonk::Window>(Gonk::Window::Create());
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