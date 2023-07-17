#include <Gonk.h>

class Sandbox : public Gonk::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Gonk::Application* Gonk::CreateApplication() 
{
	return new Sandbox();
}

