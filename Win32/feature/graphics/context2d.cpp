#include "context2d.hpp"

#pragma push_macro("SelectBrush")
#undef SelectBrush
#pragma push_macro("SelectPen")
#undef SelectPen

using namespace Graphics;

GraphicsContext2D::GraphicsContext2D(Vector2U size) {
	impl = new Impl{};
	brush = new BrushDoubleBuffer(this);
	brush->Push(new NullBrush());
	//pen->Push(new NullPen());
	Resize(size);
}

GraphicsContext2D::~GraphicsContext2D() {
	if(impl->bitmap != nullptr)
		delete impl->bitmap;
	delete impl;
}

void GraphicsContext2D::Resize(Vector2U size) {
	Legacy::Bitmap
		*oldBm = impl->bitmap,
		*newBm = new Legacy::Bitmap(size);
	if(oldBm != nullptr)
		delete oldBm;
	impl->bitmap = newBm;
	((BrushDoubleBuffer *)brush)->Select();
	//SelectPen(GetPen());
}

void GraphicsContext2D::Pixel(Vector2F pos, Color color) {
	impl->bitmap->dc->SetPixel((int)pos[0], (int)pos[1], Legacy::ColorRef(color));
}

void GraphicsContext2D::Rectangle(ScreenRect const &rect) {
	impl->bitmap->dc->Rect(rect.min[0], rect.min[1], rect.max[0], rect.max[1]);
}

#pragma pop_macro("SelectBrush")
#pragma pop_macro("SelectPen")
