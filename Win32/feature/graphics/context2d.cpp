#include "context2d.hpp"

#pragma push_macro("SelectBrush")
#undef SelectBrush
#pragma push_macro("SelectPen")
#undef SelectPen

using namespace Graphics;

GraphicsContext2D::GraphicsContext2D(Vector2U size) {
	impl = new Impl{};
	brushBuffer.Push(new NullBrush());
	penBuffer.Push(new NullPen());
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
	SelectBrush(GetBrush());
	SelectPen(GetPen());
}

void GraphicsContext2D::Pixel(Vector2F pos, Color color) {
	impl->bitmap->dc->SetPixel((int)pos[0], (int)pos[1], Legacy::ColorRef(color));
}

void GraphicsContext2D::Rectangle(ScreenRect const &rect) {
	impl->bitmap->dc->Rect(rect.min[0], rect.min[1], rect.max[0], rect.max[1]);
}

Brush *GraphicsContext2D::GetBrush() {
	return brushBuffer.front;
}

Pen *GraphicsContext2D::GetPen() {
	return penBuffer.front;
}

Brush *GraphicsContext2D::SelectBrush(Brush *brush) {
	auto old = brushBuffer.front;
	brushBuffer.front = brush;
	impl->bitmap->dc->Select(brush->impl->brush);
	return old;
}

Pen *GraphicsContext2D::SelectPen(Pen *pen) {
	auto old = penBuffer.front;
	penBuffer.front = pen;
	impl->bitmap->dc->Select(pen->impl->pen);
	return old;
}

Brush *GraphicsContext2D::PushBrush(Brush *brush) {
	auto old = brushBuffer.Push(brush);
	SelectBrush(brush);
	return old;
}

Pen *GraphicsContext2D::PushPen(Pen *pen) {
	auto old = penBuffer.Push(pen);
	SelectPen(pen);
	return old;
}

Brush *GraphicsContext2D::SwapBrush() {
	SelectBrush(brushBuffer.Swap());
	return GetBrush();
}

Pen *GraphicsContext2D::SwapPen() {
	SelectPen(penBuffer.Swap());
	return GetPen();
}

#pragma pop_macro("SelectBrush")
#pragma pop_macro("SelectPen")
