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
	using Coord2D = Vector<Float, 2>;
	using Coord3D = Vector<Float, 3>;
	using RectRange = BoxRange<Coord2D>;

	struct Color {
		union {
			Vector<Float, 4> v;
			struct {
				Float r, g, b, a;
			};
		};

		Color(std::initializer_list<Float> data) : v(data) {
			if(data.size() < 4)
				a = 1;
		}

		Color(Float r, Float g, Float b, Float a = 1) : v({ r, g, b, a }) {}

		Color() : Color(0, 0, 0, 1) {}

		Color(Color const &c) : Color(c.r, c.g, c.b, c.a) {
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		Color &operator=(Vector<Float, 4> const &v) {
			r = v[0];
			g = v[1];
			b = v[2];
			a = v[3];
			return *this;
		}
	};
}