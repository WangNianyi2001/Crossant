#pragma once

#include "Graphics/feature/graphics/context2d/pen.hpp"
#include "Win32/legacy.hpp"
#include <map>

namespace Graphics {
	struct Pen::Impl {
		Legacy::Pen *pen = nullptr;

		static std::map<Style, int> styleMap;
		static std::map<Cap, int> capMap;
		static std::map<Join, int> joinMap;

		struct Getter : Function<Legacy::GDIObject *, Pen *> {
			virtual Legacy::GDIObject *operator()(
				Pen *const &pen
				) const override {
				return pen->impl->pen;
			}
		};
	};
}
