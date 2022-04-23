#pragma once

#include "../gdi.hpp"

namespace Graphics::Win32::Legacy {
	using ColorRef = unsigned long;

	struct DeviceContext : HandledObject, Destroyable {
		DeviceContext(void *const handle) : HandledObject(handle) {}
		virtual ~DeviceContext() override = default;

		virtual void Destroy() override;

		void Select(GDIObject *object);

		void SetPixel(int x, int y, ColorRef color);
	};
}
