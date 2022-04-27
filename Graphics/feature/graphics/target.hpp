#pragma once

#include "../../common/type.hpp"

namespace Graphics {
	struct GraphicsTarget {
		struct Impl;
		Impl *impl;

		void Resize(Vector2U size);
	};
}
