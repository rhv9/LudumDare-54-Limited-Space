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
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();

	}

	void OnUpdate() override
	{
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

