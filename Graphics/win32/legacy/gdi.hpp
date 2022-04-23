#pragma once

#include "../../common/interface.hpp"
#include "../../common/types.hpp"
#include "../legacy.hpp"
#include "user.hpp"

namespace Graphics::Win32::Legacy {
	struct GDIObject : HandledObject {
		GDIObject(void *const handle) : HandledObject(handle) {}
	};

	struct DeviceContext;

	struct PaintStruct {
		void *const ps;

		PaintStruct();
		~PaintStruct();

		DeviceContext *GetDC();
	};
}

#include "gdi/bitmap.hpp"
#include "gdi/devicecontext.hpp"
