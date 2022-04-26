#pragma once

#include "context.hpp"

namespace Graphics {
	class GraphicsContext2D : public GraphicsContext {
	public:
		struct Impl;
		Impl *impl;

		GraphicsContext2D(Vector2U size);
		virtual ~GraphicsContext2D() override;

		virtual void Resize(Vector2U size) override;

		virtual void SelectBrush(Brush *brush);
		virtual void SelectPen(Pen *pen);

		virtual void Pixel(Vector2F pos, Color color);
		virtual void Rectangle(ScreenRect const &rect);
	};
}
