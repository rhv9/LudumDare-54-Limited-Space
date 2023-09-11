#pragma once

#include "Core.h"

#include "Window.h"
#include "Gonk/LayerStack.h"
#include "Gonk/Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Gonk/ImGui/ImGuiLayer.h"

#include "Gonk/Renderer/Shader.h"
#include "Gonk/Renderer/Buffer.h"
#include "Gonk/Renderer/VertexArray.h"

#include "Gonk/Renderer/Camera.h"

namespace Gonk {

	class GONK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Shutdown();

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastRenderTime;


	private:
		static Application* s_Instance;
		bool m_Minimized = false;

	};
	// To be defined in CLIENT
	Application* CreateApplication();

}

