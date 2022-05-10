#pragma once

#include "Graphics/feature/graphics/context2d/brush.hpp"
#include "Win32/legacy.hpp"

namespace Graphics {
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
