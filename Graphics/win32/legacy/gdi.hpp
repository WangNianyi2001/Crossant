#pragma once

#include "../../common/interface.hpp"
#include "../../common/types.hpp"
#include "../legacy.hpp"
#include "user.hpp"

namespace Graphics::Win32::Legacy {
	using ColorRef = unsigned long;

	struct GDIObject;

	struct DeviceContext : HandledObject, Destroyable {
		DeviceContext(void *const handle) : HandledObject(handle) {}
		virtual ~DeviceContext() override = default;

		virtual void Destroy() override;

		void Select(GDIObject *object);

		void SetPixel(int x, int y, ColorRef color);
	};

	struct GDIObject : HandledObject {
		GDIObject(void *const handle) : HandledObject(handle) {}
	};

	struct PaintStruct {
		void *const ps;

		PaintStruct();
		~PaintStruct();

		DeviceContext *GetDC();
	};
}

#include "gdi/bitmap.hpp"
