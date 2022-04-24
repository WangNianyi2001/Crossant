#pragma once

#include "../gdi.hpp"

namespace Graphics::Win32::Legacy {
	struct DeviceContext : HandledObject {
		DeviceContext(void *const handle) : HandledObject(handle) {}
		virtual ~DeviceContext() override;

		void Select(GDIObject *object);

		void SetPixel(int x, int y, Color::Hex color);
	};
}
