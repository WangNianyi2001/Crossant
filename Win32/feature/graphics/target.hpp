#pragma once

#include "Crossant/feature/graphics/target.hpp"
#include "Win32/legacy.hpp"

namespace Crossant::Graphics {
	struct Target::Impl : Legacy::Bitmap {
		Impl(Size2D size) : Legacy::Bitmap(size) {}
		Impl(Legacy::DeviceContext &dc, Size2D size) : Legacy::Bitmap(dc, size) {}
	};
}
