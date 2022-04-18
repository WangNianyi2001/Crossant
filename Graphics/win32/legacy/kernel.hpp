#pragma once

#include "legacy.hpp"

namespace Graphics::Win32::Legacy {
	struct KernelObject : HandledObject {
		KernelObject() : HandledObject(nullptr) {}
		KernelObject(void *const handle) : HandledObject(handle) {}

		virtual ~KernelObject() = default;
	};

	struct Icon : KernelObject {};

	struct Cursor : KernelObject {};
}
