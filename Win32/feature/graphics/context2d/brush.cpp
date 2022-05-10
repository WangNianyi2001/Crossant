#include "brush.hpp"
#include <Windows.h>

using namespace Graphics;

Brush::Brush() {
	impl = new Impl{};
}

Brush::~Brush() {
	delete impl;
}

NullBrush::NullBrush() {
	impl->brush = new Legacy::Brush(GetStockObject(NULL_BRUSH));
}

SolidBrush::SolidBrush(Color color) {
	impl->brush = new Legacy::Brush(CreateSolidBrush(Legacy::ColorRef(color).value));
}

SolidBrush::~SolidBrush() {
	delete impl->brush;
}
