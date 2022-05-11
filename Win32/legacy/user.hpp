#pragma once

#include "../legacy.hpp"
#include "Crossant/common/event/listener.hpp"
#include "Crossant/common/type.hpp"

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

#include "user/window.hpp"
