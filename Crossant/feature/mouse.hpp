#pragma once

#include "Crossant/common/basic.hpp"
#include <map>

namespace Crossant {
	struct Mouse {
		enum struct Button : Byte {
			Left, Middle, Right
		};
		std::map<Button, bool> buttons;
		Coord2D position;
	};
}