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

		virtual void Resize(Vector2U size) override;

		virtual Brush *GetBrush();
		virtual Pen *GetPen();
		virtual Brush *SelectBrush(Brush *brush);
		virtual Pen *SelectPen(Pen *pen);
		virtual Brush *PushBrush(Brush *brush);
		virtual Pen *PushPen(Pen *pen);
		virtual Brush *SwapBrush();
		virtual Pen *SwapPen();

		virtual void Pixel(Vector2F pos, Color color);
		virtual void Rectangle(ScreenRect const &rect);
	};
}
