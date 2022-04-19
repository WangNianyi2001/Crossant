#pragma once

#include "../drawingcontext.hpp"
#include "window.hpp"

namespace Graphics::Win32 {
	class DrawingContext : public Graphics::DrawingContext<Window *> {
	protected:
		Window *const window;

	public:
		DrawingContext(Window *window) : window(window) {}
		virtual ~DrawingContext() override = default;

		virtual void Draw() override;
	};
}
