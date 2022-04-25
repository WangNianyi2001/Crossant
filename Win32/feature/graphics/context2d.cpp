#include "context2d.hpp"

using namespace Graphics;

GraphicsContext2D::GraphicsContext2D(Vector2U size) {
	impl = new Impl{};
	Resize(size);
}

GraphicsContext2D::~GraphicsContext2D() {
	if(impl->bitmap != nullptr)
		delete impl->bitmap;
	delete impl;
}

void GraphicsContext2D::Resize(Vector2U size) {
	if(impl->bitmap != nullptr)
		delete impl->bitmap;
	impl->bitmap = new Legacy::Bitmap(size);
}

void GraphicsContext2D::Pixel(Vector2F pos, Color color) {
	impl->bitmap->dc->SetPixel((int)pos[0], (int)pos[1], Legacy::ColorRef(color));
}

#pragma push_macro("SelectBrush")
#undef SelectBrush
void GraphicsContext2D::SelectBrush(Brush *brush) {
	impl->bitmap->dc->Select(brush->impl->brush);
}
#pragma pop_macro("SelectBrush")

#pragma push_macro("SelectPen")
#undef SelectPen
void GraphicsContext2D::SelectPen(Pen *pen) {
	impl->bitmap->dc->Select(pen->impl->pen);
}
#pragma pop_macro("SelectPen")
