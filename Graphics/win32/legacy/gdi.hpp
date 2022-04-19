#pragma once

#include "../legacy.hpp"
#include "user.hpp"

namespace Graphics::Win32::Legacy {
	struct GDIObject : HandledObject {
		GDIObject(void *const handle) : HandledObject(handle) {}
	};

	struct Brush : GDIObject {};
}
