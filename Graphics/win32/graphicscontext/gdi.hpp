#pragma once

#include "../../feature/graphicscontext.hpp"
#include "../window.hpp"
#include "../legacy/gdi.hpp"
#include "../../common/types.hpp"

namespace Graphics::Win32 {
	class GDIContext : public Graphics::GraphicsContext2D {
	protected:
		Window *const window;
		Legacy::Bitmap *bitmap = nullptr;

	public:
		GDIContext(Window *window);
		virtual ~GDIContext() override;

		virtual void Resize(Vector2U size) override;

		virtual void Pixel(Vector2F pos, Color3B color) override;
	};
}
