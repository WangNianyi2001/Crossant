#pragma once

#include "Crossant/feature/graphics/2d/pen.hpp"
#include <Windows.h>
#include <map>

namespace Crossant::Graphics::Graphics2D {
	struct Pen::Impl {
		HPEN hPen;

		static std::map<Style, int> styleMap;
		static std::map<Cap, int> capMap;
		static std::map<Join, int> joinMap;

		struct Getter {
			inline HPEN operator()(Pen *pen) const {
				return pen->impl->hPen;
			}
		};
	};
}
