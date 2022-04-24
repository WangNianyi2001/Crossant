#pragma once

#include "../feature/application.hpp"
#include "window.hpp"
#include "legacy/user.hpp"

namespace Graphics::Win32 {
	class Application : public Graphics::Application {
		friend class Window;

	protected:
		Legacy::ModuleInstance *const instance;

	public:
		Application(Legacy::ModuleInstance *instance);
		virtual ~Application() override;

		virtual Window *CreateWindow() override;
	};
}
