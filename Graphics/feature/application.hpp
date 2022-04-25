#pragma once

#include "window.hpp"

namespace Graphics {
	class Application {
	public:
		static inline Application *current = nullptr;

		static int Main();

		struct Impl;
		Impl *impl;

		Application();
		virtual ~Application();

		Window *CreateWindow();
	};
}
