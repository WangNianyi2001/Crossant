#pragma once

#include "Graphics/graphics.hpp"
#include "../../legacy.hpp"

namespace Graphics {
	struct Brush::Impl {
		Legacy::Brush *brush;
	};
}
