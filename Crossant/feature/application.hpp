#pragma once

#include "Crossant/common/type.hpp"
#include "window.hpp"

namespace Crossant {
	struct Application {
		static inline Application *current = nullptr;

		static int Main();

		struct Impl;
		Impl *impl;

		Application();
		virtual ~Application();

		Window *CreateWindow();
	};
}
