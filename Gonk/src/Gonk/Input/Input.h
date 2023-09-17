#pragma once
#include <utility>

#include "KeyCodes.h"

namespace Gonk {

	class Input
	{
	public:
		static bool IsKeyPressed(Key keyCode);
		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePosition();
	};

}
