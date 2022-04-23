#pragma once

#include "../graphicscontext.hpp"
#include "../window.hpp"
#include "../legacy/gdi.hpp"
#include "../../common/types.hpp"

namespace Graphics::Win32 {
	class GDIContext : public GraphicsContext {
	protected:
		Legacy::DeviceContext *dc = nullptr;
		Legacy::Bitmap *bitmap = nullptr;

	public:
		GDIContext(Window *window);
		virtual ~GDIContext() = default;

		virtual void Render() override;
		virtual void Resize(Vector2U size) override;

		void Pixel(Vector2F pos, Color3B color);
	};
}
