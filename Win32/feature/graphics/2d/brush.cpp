#include "brush.hpp"
#include <Windows.h>
#include "Win32/utility.hpp"

using namespace Crossant::Graphics::Graphics2D;

Brush::Brush() {
	impl = new Impl{};
}

Brush::~Brush() {
	delete impl;
}

NullBrush::NullBrush() {
	impl->hBr = (HBRUSH)GetStockObject(NULL_BRUSH);
}

SolidBrush::SolidBrush(Color color) {
	impl->hBr = CreateSolidBrush(ColorToRef(color));
}

SolidBrush::~SolidBrush() {
	DeleteObject(impl->hBr);
}
