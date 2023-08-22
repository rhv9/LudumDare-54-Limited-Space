#include <Gonk.h>


class ExampleLayer : public Gonk::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GK_INFO("ExampleLayer::Update");
	}

	void OnEvent(Gonk::Event& event)
	{
		GK_TRACE("{0}", event);
	}
};


class Sandbox : public Gonk::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Gonk::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Gonk::Application* Gonk::CreateApplication() 
{
	return new Sandbox();
}

