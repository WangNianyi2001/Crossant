#pragma once

#include <xstring>
#include "range.hpp"
#include "vector.hpp"

namespace Crossant {
	using Byte = unsigned __int8;
	using Float = float;
#ifdef UNICODE
	using Char = wchar_t;
#else
	using Char = char;
#endif
	using String = std::basic_string<Char>;

	constexpr Float PI = 3.14159265359f;

	using Size2D = Vector<unsigned, 2>;
	using Color = Vector<Float, 3>;
	using Coord2D = Vector<Float, 2>;
	using Coord3D = Vector<Float, 3>;
	using RectRange = BoxRange<Coord2D>;
}