#pragma once

#include "types/vector.hpp"

namespace Graphics {
	// Vector

	using Vector2U = Vector<unsigned, 2>;
	using Vector2I = Vector<int, 2>;
	using Vector2F = Vector<float, 2>;

	// Screen coordinate

	//struct ScreenCoord : Vector2I {
	//	bool operator<(ScreenCoord const &coord) {
	//		return operator[0] <=
	//	}
	//};

	//template<typename Point>
	//struct Range {
	//	virtual bool Contains(Point point) = 0;
	//};

	//template<typename Point>
	//struct MinMaxRange : Range<Point> {
	//	Point const min, max;

	//	MinMaxRange(Point min, Point max) : min(min), max(max) {}

	//	virtual bool Contains(Point point) override {
	//		return point >= min && point < max;	// Left-close right-open
	//	}
	//};

	//struct ScreenRect : MinMaxRange<ScreenCoord> {};

	// Color

	using Color3F = Vector<float, 3>;
	using Color3B = Vector<unsigned __int8, 3>;
}
