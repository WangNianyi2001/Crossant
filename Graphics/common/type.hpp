#pragma once

#include "type/tuple.hpp"
#include "type/vector.hpp"
#include "type/range.hpp"
#include <xstring>

namespace Graphics {
	// Text
#ifdef UNICODE
	using Char = wchar_t;
#else
	using Char = char;
#endif
	using String = std::basic_string<Char>;

	// Vector

	using Vector2U = Vector<unsigned, 2>;
	using Vector2I = Vector<int, 2>;
	using Vector2F = Vector<float, 2>;

	using Color = Vector<float, 3>;

	// Screen geometries

	using ScreenCoord = Vector2I;
	using ScreenRect = BoxRange<ScreenCoord>;
}
