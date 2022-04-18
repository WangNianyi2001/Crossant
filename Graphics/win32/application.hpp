#pragma once

#include "../application.hpp"
#include "window.hpp"
#include "legacy/user.hpp"

namespace Graphics::Win32 {
	class Application : public Graphics::Application {
	protected:
		Legacy::ModuleInstance *const instance;

	public:
		Legacy::WindowClass *defaultWindowClass;

		virtual Window *CreateWindow() override;

		Application(Legacy::ModuleInstance *instance);
	};
}
