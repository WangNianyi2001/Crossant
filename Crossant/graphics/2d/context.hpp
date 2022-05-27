#pragma once

#include "Crossant/common/buffer.hpp"
#include "../context.hpp"
#include "../target.hpp"
#include "brush.hpp"
#include "pen.hpp"

namespace Crossant::Graphics::Graphics2D {
	struct Context : Graphics::Context {
		DoubleBuffer<Brush *> *brush;
		DoubleBuffer<Pen *> *pen;

		Context(Graphics::Target &target);
		virtual ~Context() override;

		virtual void MakeCurrent() const override;
		void OnResize() override;

		// Drawings
		void Pixel(Coord2D pos, Color color) const;
		void Rectangle(RectRange const &rect) const;
	};
}
