#pragma once

#include "Core.h"

namespace Gonk {

	class GONK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
	};
	// To be defined in CLIENT
	Application* CreateApplication();

}

