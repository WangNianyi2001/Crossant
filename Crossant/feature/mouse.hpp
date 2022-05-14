#pragma once

#include "Crossant/common/basic.hpp"

namespace Crossant {
	struct Mouse {
		enum struct Button : Byte {
			Left, Middle, Right
		};
		static bool Pressed(Button button);
		static inline Coord2D position{};
	};
}