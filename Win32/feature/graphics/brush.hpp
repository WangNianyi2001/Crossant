#pragma once

#include "Graphics/graphics.hpp"
#include "../../legacy.hpp"

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
