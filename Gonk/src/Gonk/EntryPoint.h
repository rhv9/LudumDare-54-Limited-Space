#pragma once

#ifdef GK_PLATFORM_WINDOWS

extern Gonk::Application* Gonk::CreateApplication();

int main() 
{
	Gonk::Log::Init();
	GK_CORE_WARN("Initialized Log!");
	int b = 3;
	GK_INFO("Howdee there! Var={0}", b);

	auto app = Gonk::CreateApplication();
	app->Run();
	delete app;
}

#endif