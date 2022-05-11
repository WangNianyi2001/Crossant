#pragma once

#include "Crossant/feature/graphics/2d/brush.hpp"
#include "Win32/legacy.hpp"

namespace Crossant::Graphics::Graphics2D {
	struct Brush::Impl {
		Legacy::Brush *brush;

		struct Getter : Function<Legacy::GDIObject *, Brush *> {
			virtual Legacy::GDIObject *operator()(
				Brush *const &brush
				) const override {
				return brush->impl->brush;
			}
		};
	};
}
