#include "context.hpp"

#pragma push_macro("SelectBrush")
#undef SelectBrush
#pragma push_macro("SelectPen")
#undef SelectPen

using namespace Crossant::Graphics::Graphics2D;

Context::Context(Graphics::Target &target) : Graphics::Context(target) {
	brush = new BrushBuffer(*this);
	brush->Push(new NullBrush());
	pen = new PenBuffer(*this);
	pen->Push(new NullPen());
	OnResize();
}

Context::~Context() = default;

void Context::MakeCurrent() const {}

void Context::OnResize() {
	((BrushBuffer *)brush)->Select();
	((PenBuffer *)pen)->Select();
}

void Context::Pixel(Coord2D pos, Color color) const {
	SetPixel(
		target.impl->hDC,
		(int)pos[0], (int)pos[1],
		Legacy::ColorRef::ToHex(color)
	);
}

void Context::Rectangle(RectRange const &rect) const {
	::Rectangle(
		target.impl->hDC,
		(int)rect.min[0], (int)rect.min[1],
		(int)rect.max[0], (int)rect.max[1]
	);
}

#pragma pop_macro("SelectBrush")
#pragma pop_macro("SelectPen")
