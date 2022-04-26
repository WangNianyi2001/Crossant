#pragma once

#include "context.hpp"

namespace Graphics {
	struct GraphicsContext2D : GraphicsContext {
		struct Impl;
		Impl *impl;

		DoubleBuffer<Brush *> *brush;
		DoubleBuffer<Pen *> *pen;

		GraphicsContext2D(Vector2U size);
		virtual ~GraphicsContext2D() override;

		void Resize(Vector2U size) override;

		void Pixel(Vector2F pos, Color color);
		void Rectangle(ScreenRect const &rect);
	};
}
