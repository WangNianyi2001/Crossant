#pragma once

#include "../legacy.hpp"
#include "../../common/event/listener.hpp"
#include "../../common/type.hpp"

namespace Graphics::Win32::Legacy {
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
