#pragma once

namespace Graphics {
	template<typename Coord, int dimension>
	using Point = Coord[dimension];

	using Point2I = Point<int, 2>;
	using Point2F = Point<float, 2>;
}
