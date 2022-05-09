#include "context2d.hpp"

#pragma push_macro("SelectBrush")
#undef SelectBrush
#pragma push_macro("SelectPen")
#undef SelectPen

using namespace Graphics;

void PutTo(GraphicsContext2D *gc) {
}

GraphicsContext2D::GraphicsContext2D(Vector2U size) : target(size) {
	((BrushBuffer *)brush)->Select();
	((PenBuffer *)pen)->Select();
	brush = new BrushBuffer(this);
	brush->Push(new NullBrush());
	pen = new PenBuffer(this);
	pen->Push(new NullPen());
	Configure(std::bind(&PutTo, this));
}

GraphicsContext2D::~GraphicsContext2D() = default;

void GraphicsContext2D::Resize(Vector2U size) {
	target.Resize(size);
	((BrushBuffer *)brush)->Select();
	((PenBuffer *)pen)->Select();
}

void GraphicsContext2D::Pixel(Vector2F pos, Color color) {
	target.impl->dc->SetPixel(
		(int)pos[0], (int)pos[1],
		Legacy::ColorRef(color)
	);
}

void GraphicsContext2D::Rectangle(ScreenRect const &rect) {
	target.impl->dc->Rect(
		rect.min[0], rect.min[1],
		rect.max[0], rect.max[1]
	);
}

#pragma pop_macro("SelectBrush")
#pragma pop_macro("SelectPen")
