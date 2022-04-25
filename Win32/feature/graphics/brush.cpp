#include "brush.hpp"

using namespace Graphics;

Brush::Brush() {
	impl = new Impl{};
}

Brush::~Brush() {
	delete impl;
}

SolidBrush::SolidBrush(Color color) {
	impl->brush = new Legacy::SolidBrush(Legacy::ColorRef(color));
}

SolidBrush::~SolidBrush() {
	delete impl->brush;
}
