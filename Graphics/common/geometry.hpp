#pragma once

namespace Graphics {
	template<typename Coord, int dimension>
	using Point = Coord[dimension];

	using Point2F = Point<float, 2>;
}
