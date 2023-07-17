#pragma once

#ifdef GK_PLATFORM_WINDOWS

extern Gonk::Application* Gonk::CreateApplication();

int main() 
{
	auto app = Gonk::CreateApplication();
	app->Run();
	delete app;
}

#endif