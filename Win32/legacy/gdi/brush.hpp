#pragma once

#include "../gdi.hpp"

namespace Graphics::Legacy {
	struct Brush : GDIObject {
		Brush(void *handle) : GDIObject(handle) {}
	};

	struct SolidBrush : Brush {
		SolidBrush(void *handle) : Brush(handle) {}
		SolidBrush(ColorRef color);

		virtual ~SolidBrush();
	};
}
