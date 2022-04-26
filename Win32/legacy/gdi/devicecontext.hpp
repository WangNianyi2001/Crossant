#pragma once

#include "../gdi.hpp"

namespace Graphics::Legacy {
	struct DeviceContext : HandledObject {
		DeviceContext(void *const handle) : HandledObject(handle) {}
		virtual ~DeviceContext() override;

		void Select(GDIObject *object);

		void SetPixel(int x, int y, ColorRef color);
		void Rect(int left, int top, int right, int bottom);
	};
}
