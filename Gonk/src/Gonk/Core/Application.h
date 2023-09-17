#pragma once

#include "Core.h"

#include "Window.h"
#include "Gonk/Core/LayerStack.h"
#include "Gonk/Events/Event.h"
#include "Gonk/Events/ApplicationEvent.h"

#include "Gonk/ImGui/ImGuiLayer.h"

#include "Gonk/Renderer/Shader.h"
#include "Gonk/Renderer/Buffer.h"
#include "Gonk/Renderer/VertexArray.h"

#include "Gonk/Renderer/Camera.h"

int main(int argc, char** argv);

namespace Gonk {

	class GONK_API Application
	{
	public:
		Application(const std::string& name = "Gonk App");
		virtual ~Application();


		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();
		void Shutdown();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastRenderTime;

	private:
		static Application* s_Instance;
		bool m_Minimized = false;

		friend int ::main(int argc, char** argv);

	};
	// To be defined in CLIENT
	Application* CreateApplication();

}

