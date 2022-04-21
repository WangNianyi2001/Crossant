#pragma once

#include "../feature/graphicscontext.hpp"
#include "window.hpp"

namespace Graphics::Win32 {
	class GraphicsContext : public Graphics::GraphicsContext<Window *> {
	protected:
		Window *const window;

	public:
		GraphicsContext(Window *window) : window(window) {}
		virtual ~GraphicsContext() override = default;
	};
}
