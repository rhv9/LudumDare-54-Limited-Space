#include <Gonk.h>

#include <imgui/imgui.h>

class ExampleLayer : public Gonk::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

	}

	void OnUpdate() override
	{
		auto [x, y] = Gonk::Input::GetMousePosition();
		GK_TRACE("{0}", Gonk::Input::IsKeyPressed(GK_KEY_W));
	}

	void OnEvent(Gonk::Event& event)
	{
	}
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

