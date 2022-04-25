#pragma once

#include "../gdi.hpp"

namespace Graphics::Legacy {
	struct Pen : GDIObject {
		Pen(void *handle) : GDIObject(handle) {}
	};

	struct CosmeticPen : Pen {
		CosmeticPen(int width, ColorRef color);
	};
}
