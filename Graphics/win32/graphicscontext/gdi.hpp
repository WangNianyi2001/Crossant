#pragma once

#include "../graphicscontext.hpp"
#include "../window.hpp"
#include "../legacy/gdi.hpp"
#include "../../common/color.hpp"
#include "../../common/geometry.hpp"

namespace Graphics::Win32 {
	class GDIContext : public GraphicsContext {
	protected:
		Legacy::PaintStruct paintStruct;
		Legacy::DeviceContext *dc;

	public:
		GDIContext(Window *window) : GraphicsContext(window) {}
		virtual ~GDIContext() = default;

		virtual void Begin() override;
		virtual void End() override;

		void Pixel(Point2F pos, Color3B color);
	};
}
