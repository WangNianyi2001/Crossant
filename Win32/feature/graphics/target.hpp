#pragma once

#include "Graphics/feature/graphics/target.hpp"
#include "Win32/legacy.hpp"

namespace Graphics {
	struct GraphicsTarget::Impl : Legacy::Bitmap {
		Impl(Size2D size) : Legacy::Bitmap(size) {}
		Impl(Legacy::DeviceContext &dc) : Legacy::Bitmap(dc) {}
	};
}