#pragma once

#include "Gonk/Core/Core.h"

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
	GK_PROFILE_BEGIN_SESSION("Startup", "Profiling/GonkProfile-Startup.json");
	auto app = Gonk::CreateApplication();
	GK_PROFILE_END_SESSION();

	GK_PROFILE_BEGIN_SESSION("Runtime", "Profiling/GonkProfile-Runtime.json");
	app->Run();
	GK_PROFILE_END_SESSION();

	GK_PROFILE_BEGIN_SESSION("Closing", "Profiling/GonkProfile-Closing.json");
	delete app;
	GK_PROFILE_END_SESSION();

}

#endif