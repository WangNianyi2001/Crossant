#pragma once

#include "window.hpp"
#include "legacy/user.hpp"

namespace Graphics::Win32 {
	class Application {
	protected:
		Legacy::ModuleInstance *const instance;

	public:
		static Application *current;

		static int Main();

		Legacy::WindowClass *defaultWindowClass;

		Window *CreateWindow(Window::CreationArguments arguments);

		Application(Legacy::ModuleInstance *instance);
	};
}
