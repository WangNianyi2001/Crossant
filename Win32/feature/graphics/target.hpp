#pragma once

#include "../../win32.hpp"

namespace Graphics {
	struct GraphicsTarget::Impl {
		Legacy::Bitmap* bitmap = nullptr;
	};
}