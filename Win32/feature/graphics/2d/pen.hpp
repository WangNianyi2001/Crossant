#pragma once

#include "Crossant/feature/graphics/2d/pen.hpp"
#include "Win32/legacy.hpp"
#include <map>

namespace Crossant::Graphics::Graphics2D {
	struct Pen::Impl {
		Legacy::Pen *pen = nullptr;

		static std::map<Style, int> styleMap;
		static std::map<Cap, int> capMap;
		static std::map<Join, int> joinMap;

		struct Getter : Function<Legacy::GDIObject *, Pen *> {
			inline virtual Legacy::GDIObject *	operator()(Pen *pen) const override {
				return pen->impl->pen;
			}
		};
	};
}
