#pragma once

#ifdef GK_PLATFORM_WINDOWS

// TODO: Temporary fix to force dedicated GPU to be the renderer!
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

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