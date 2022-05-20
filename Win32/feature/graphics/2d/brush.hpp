#pragma once

#include "Crossant/feature/graphics/2d/brush.hpp"
#include <Windows.h>

namespace Crossant::Graphics::Graphics2D {
	struct Brush::Impl {
		HBRUSH hBr;

		struct Getter {
			inline HBRUSH operator()(Brush *brush) const {
				return brush->impl->hBr;
			}
		};
	};
}
