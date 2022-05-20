#include "utility.hpp"

COLORREF Crossant::ColorToChannel(Color color, unsigned i) {
	return (COLORREF)(0xffU * color[i]) & 0xffU;
}

COLORREF Crossant::ColorToRef(Color color) {
	return ColorToChannel(color, 0) |
		(ColorToChannel(color, 1) << 8) |
		(ColorToChannel(color, 2) << 16);
}

void Crossant::TryThrowLastError() {
	int code = GetLastError();
	if(code == 0)
		return;
	throw code;
}