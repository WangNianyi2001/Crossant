#pragma once

#include "vector.hpp"

namespace Graphics {
	struct Color : Vector<float, 3> {
		using Hex = unsigned __int32;

		Color(float r, float g, float b) : Vector{ r, g, b } {}

		inline unsigned __int32 ChannelHex(unsigned i) const {
			return ((Hex)(0xffU * operator[](i)) & 0xffU);
		}

		inline unsigned __int32 ToHex() const {
			return ChannelHex(0) |
				(ChannelHex(1) << 8) |
				(ChannelHex(2) << 16);
		}
	};
}
