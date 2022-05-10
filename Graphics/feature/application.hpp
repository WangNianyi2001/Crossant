#pragma once

#include "Graphics/common/type.hpp"
#include "window.hpp"

namespace Graphics {
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
