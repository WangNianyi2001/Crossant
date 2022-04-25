#pragma once

#include "../legacy.hpp"

namespace Graphics::Legacy {
	struct KernelObject : HandledObject {
		KernelObject() : HandledObject(nullptr) {}
		KernelObject(void *const handle) : HandledObject(handle) {}

		virtual ~KernelObject() override = default;
	};

	struct Icon : KernelObject {};

	struct Cursor : KernelObject {};
}
