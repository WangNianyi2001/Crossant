#pragma once

#include "Graphics/graphics.hpp"
#include "../../legacy.hpp"

namespace Graphics {
	struct Pen::Impl {
		Legacy::Pen *pen;
	};
}
