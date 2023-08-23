#include "gkpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/ImGuiGLFWImpl.h"

#include "Gonk/Application.h"

// TEMPORARY
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void UpdateKeyModifiers(ImGuiKey imguiKey, bool keyDown)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (imguiKey)
	{
		case  ImGuiKey_LeftCtrl:
		case ImGuiKey_RightCtrl:
			io.AddKeyEvent(ImGuiMod_Ctrl, keyDown);
			break;
		case  ImGuiKey_LeftShift:
		case ImGuiKey_RightShift:
			io.AddKeyEvent(ImGuiMod_Shift, keyDown);
			break;
		case  ImGuiKey_LeftAlt:
		case ImGuiKey_RightAlt:
			io.AddKeyEvent(ImGuiMod_Alt, keyDown);
			break;
		case  ImGuiKey_LeftSuper:
		case ImGuiKey_RightSuper:
			io.AddKeyEvent(ImGuiMod_Super, keyDown);
			break;
	}
}

namespace Gonk {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGuiIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// keymaps add

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		// MouseEvents
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolledEvent, this, std::placeholders::_1));
		// KeyEvents
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
		// WindowEvents
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		//ImGui_ImplGlfw_UpdateKeyModifiers(window);
		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 && e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (e.GetMouseButton() >= 0 && e.GetMouseButton() < ImGuiMouseButton_COUNT)
			io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddMousePosEvent((float)e.GetX(), (float)e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddMouseWheelEvent((float)e.GetXOffset(), (float)e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		//ImGui_ImplGlfw_UpdateKeyModifiers(&application.GetWindow().);
		ImGuiIO& io = ImGui::GetIO();


		int key = ImGui_ImplGlfw_TranslateUntranslatedKey(e.GetKeyCode(), e.GetScanCode());
		ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(key);
		io.AddKeyEvent(imgui_key, true);
		
		UpdateKeyModifiers(imgui_key, true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		int key = ImGui_ImplGlfw_TranslateUntranslatedKey(e.GetKeyCode(), e.GetScanCode());
		ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(key);
		io.AddKeyEvent(imgui_key, false);

		UpdateKeyModifiers(imgui_key, false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.getWidth(), e.getHeight());
		return false;
	}


}