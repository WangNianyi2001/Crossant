#pragma once

#include "type/just.hpp"
#include "type/tuple.hpp"
#include "type/vector.hpp"
#include "type/range.hpp"
#include "type/buffer.hpp"
#include <xstring>

namespace Crossant {
	// Basic types
	using Byte = unsigned __int8;
	using Float = float;

	// Text
#ifdef UNICODE
	using Char = wchar_t;
#else
	using Char = char;
#endif
	using String = std::basic_string<Char>;

	// Vectors
	using Size2D = Vector<unsigned, 2>;
	using Color = Vector<Float, 3>;

	// Screen geometries

	using Coord2D = Vector<Float, 2>;
	using RectRange = BoxRange<Coord2D>;

	// Space geometries
	using Coord3D = Vector<Float, 3>;
}
