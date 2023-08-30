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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


	private:
		static Application* s_Instance;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;

		std::unique_ptr<Shader> m_BlueShader;
		std::unique_ptr<VertexArray> m_BlueVertexArray;
	};
	// To be defined in CLIENT
	Application* CreateApplication();

}

