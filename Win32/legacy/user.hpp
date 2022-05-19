#pragma once

#include "../legacy.hpp"
#include "Crossant/common/listener.hpp"

namespace Crossant::Legacy {
	struct UserObject : HandledObject {
		UserObject(void *const handle) : HandledObject(handle) {}

		virtual ~UserObject() override = default;
	};

	struct ModuleInstance : UserObject {
		ModuleInstance(void *const handle) : UserObject(handle) {}
	};

	struct Menu : UserObject {
		Menu(void *const handle) : UserObject(handle) {}
	};
}
