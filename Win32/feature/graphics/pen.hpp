#pragma once

#include "Graphics/graphics.hpp"
#include "../../legacy.hpp"
#include <map>

namespace Graphics {
	struct Pen::Impl {
		Legacy::Pen *pen = nullptr;

		static std::map<Style, int> styleMap;
		static std::map<Cap, int> capMap;
		static std::map<Join, int> joinMap;
	};
}
