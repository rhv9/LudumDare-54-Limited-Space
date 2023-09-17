#pragma once

// From glfw3.h

namespace Gonk {

	enum class MouseButton : uint16_t
	{
        D1         = 0,
        D2         = 1,
        D3         = 2,
        D4         = 3,
        D5         = 4,
        D6         = 5,
        D7         = 6,
        D8         = 7,
        LAST       = D8,
        LEFT       = D1,
        RIGHT      = D2,
        MIDDLE     = D3,
	};

    inline std::ostream& operator<<(std::ostream& os, MouseButton button)
    {
        os << (uint32_t)button;
        return os;
    }

}
