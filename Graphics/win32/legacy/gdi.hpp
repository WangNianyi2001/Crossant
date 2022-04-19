#pragma once

#include "../../common/interface.hpp"
#include "../legacy.hpp"
#include "user.hpp"

namespace Graphics::Win32::Legacy {
	struct GDIObject : HandledObject {
		GDIObject(void *const handle) : HandledObject(handle) {}
	};

	using ColorRef = unsigned long;

	struct DeviceContext : GDIObject, Destroyable {
		DeviceContext(void *const handle) : GDIObject(handle) {}
		virtual ~DeviceContext() override = default;

		virtual void Destroy() override;

		void SetPixel(int x, int y, ColorRef color);
	};

	struct PaintStruct {
		void *const ps;

		PaintStruct();
		~PaintStruct();

		DeviceContext *GetDC();
	};
}
