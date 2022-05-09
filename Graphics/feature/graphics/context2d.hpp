#pragma once

#include "target.hpp"
#include "brush.hpp"
#include "pen.hpp"

namespace Graphics {
	struct GraphicsContext2D : GraphicsContext {
		DoubleBuffer<Brush *> *brush;
		DoubleBuffer<Pen *> *pen;

		GraphicsContext2D(GraphicsTarget &target);
		virtual ~GraphicsContext2D() override;

		virtual void MakeCurrent() const override;
		void Resize(Vector2U size) override;

		void Pixel(Vector2F pos, Color color) const;
		void Rectangle(ScreenRect const &rect) const;
	};
}
