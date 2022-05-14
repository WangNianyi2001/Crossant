#pragma once

#include "Crossant/feature/graphics/2d/brush.hpp"
#include "Win32/legacy.hpp"

namespace Crossant::Graphics::Graphics2D {
	struct Brush::Impl {
		Legacy::Brush *brush;

		struct Getter : Function<Legacy::GDIObject *, Brush *> {
			inline virtual Legacy::GDIObject *operator()(Brush *brush) const override {
				return brush->impl->brush;
			}
		};
	};
}
