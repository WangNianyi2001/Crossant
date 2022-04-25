#include "pen.hpp"

using namespace Graphics;

Pen::Pen() {
	impl = new Impl{};
}

Pen::~Pen() {
	delete impl;
}

SimplePen::SimplePen(unsigned width, Color color) {
	impl->pen = new Legacy::CosmeticPen(width, Legacy::ColorRef(color));
}

SimplePen::~SimplePen() {
	delete impl->pen;
}
