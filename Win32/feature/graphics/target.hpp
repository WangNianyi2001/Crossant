#pragma once

#include "../../win32.hpp"

namespace Graphics {
	struct GraphicsTarget::Impl : Legacy::Bitmap {
		Impl(Size2D size) : Legacy::Bitmap(size) {}
		Impl(Legacy::DeviceContext &dc) : Legacy::Bitmap(dc) {}
	};
}