#pragma once

#include "Crossant/utility.hpp"
#include <sstream>
#include <Windows.h>

namespace Crossant {
	inline COLORREF ColorToChannel(Color color, unsigned i) {
		return (COLORREF)(0xffU * color.v[i]) & 0xffU;
	}

	inline COLORREF ColorToRef(Color color) {
		return ColorToChannel(color, 0) |
			(ColorToChannel(color, 1) << 8) |
			(ColorToChannel(color, 2) << 16);
	}

	inline Float ByteToChannel(Byte byte) {
		return (Float)byte / 256.f;
	}

	void TryThrowLastError();
}