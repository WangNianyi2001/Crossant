#pragma once

#include "../../win32.hpp"

namespace Graphics {
	struct GraphicsContext2D::Impl {
		Window *window = nullptr;
		Legacy::Bitmap *bitmap = nullptr;
	};
}
