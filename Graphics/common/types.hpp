#pragma once

#include "types/vector.hpp"

namespace Graphics {
	// Vector

	using Vector2U = Vector<unsigned, 2>;
	using Vector2I = Vector<int, 2>;
	using Vector2F = Vector<float, 2>;

	// Screen coordinate

	template<typename Point>
	struct Range {
		virtual bool Contains(Point point) const = 0;
	};

	template<typename Point>
	struct BoxRange : Range<Point> {
		Point const min, max;

		BoxRange(Point min, Point max) : min(min), max(max) {}

		virtual bool Contains(Point point) const override {
			return point >= min && point < max;	// Left-close right-open
		}
	};

	using ScreenRect = BoxRange<Vector2I>;

	// Color

	using Color3F = Vector<float, 3>;
	using Color3B = Vector<unsigned __int8, 3>;
}
