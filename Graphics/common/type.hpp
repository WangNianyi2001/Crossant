#pragma once

#include "type/vector.hpp"
#include "type/range.hpp"
#include "type/color.hpp"

namespace Graphics {
	// Vector

	using Vector2U = Vector<unsigned, 2>;
	using Vector2I = Vector<int, 2>;
	using Vector2F = Vector<float, 2>;

	// Screen coordinate

	using ScreenCoord = Vector2I;
	using ScreenRect = BoxRange<ScreenCoord>;
}
