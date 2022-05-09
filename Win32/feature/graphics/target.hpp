#pragma once

#include "../../win32.hpp"

namespace Graphics {
	struct GraphicsTarget::Impl : Legacy::Bitmap {
		Impl(Vector2U size) : Legacy::Bitmap(size) {}
	};
}