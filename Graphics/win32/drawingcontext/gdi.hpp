#pragma once

#include "../drawingcontext.hpp"
#include "../window.hpp"

namespace Graphics::Win32 {
	class GDIContext : public DrawingContext {
	protected:

	public:
		GDIContext(Window *window) : DrawingContext(window) {}
		virtual ~GDIContext() override {}

		void Line();
	};
}
