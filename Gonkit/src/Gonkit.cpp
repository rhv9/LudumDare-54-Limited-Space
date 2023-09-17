#include <Gonk.h>
#include <Gonk/Core/EntryPoint.h>

#include "GonkitLayer.h"

namespace Gonk {

	class Gonkit : public Application
	{
	public:
		Gonkit(const std::string& name)
			: Application(name)
		{
			PushLayer(new GonkitLayer());
		}

		~Gonkit()
		{

		}
	};

	Gonk::Application* CreateApplication() 
	{
		return new Gonkit("Gonkit");
	}

}

