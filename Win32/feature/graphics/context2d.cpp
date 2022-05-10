#include "context2d.hpp"

#pragma push_macro("SelectBrush")
#undef SelectBrush
#pragma push_macro("SelectPen")
#undef SelectPen

using namespace Graphics;

GraphicsContext2D::GraphicsContext2D(GraphicsTarget &target) : GraphicsContext(target) {
	brush = new BrushBuffer(*this);
	brush->Push(new NullBrush());
	pen = new PenBuffer(*this);
	pen->Push(new NullPen());
	OnResize();
}

GraphicsContext2D::~GraphicsContext2D() = default;

void GraphicsContext2D::MakeCurrent() const {}

void GraphicsContext2D::OnResize() {
	((BrushBuffer *)brush)->Select();
	((PenBuffer *)pen)->Select();
}

void GraphicsContext2D::Pixel(Coord2D pos, Color color) const {
	target.impl->dc.SetPixel(
		(int)pos[0], (int)pos[1],
		Legacy::ColorRef(color)
	);
}

void GraphicsContext2D::Rectangle(RectRange const &rect) const {
	target.impl->dc.Rectangle(
		(int)rect.min[0], (int)rect.min[1],
		(int)rect.max[0], (int)rect.max[1]
	);
}

#pragma pop_macro("SelectBrush")
#pragma pop_macro("SelectPen")
