#pragma once

#include "context.hpp"

namespace Graphics {
	class GraphicsContext2D : public GraphicsContext {
	protected:
		DoubleBuffer<Brush *> brushBuffer;
		DoubleBuffer<Pen *> penBuffer;

	public:
		struct Impl;
		Impl *impl;

		GraphicsContext2D(Vector2U size);
		virtual ~GraphicsContext2D() override;

		void Resize(Vector2U size) override;

		Brush *GetBrush();
		Pen *GetPen();
		Brush *SelectBrush(Brush *brush);
		Pen *SelectPen(Pen *pen);
		Brush *PushBrush(Brush *brush);
		Pen *PushPen(Pen *pen);
		Brush *SwapBrush();
		Pen *SwapPen();

		void Pixel(Vector2F pos, Color color);
		void Rectangle(ScreenRect const &rect);
	};
}
