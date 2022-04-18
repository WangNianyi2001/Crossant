#pragma once

#include "window.hpp"

namespace Graphics {
	class Application {
	public:
		static inline Application *current = nullptr;

		static int Main();

		virtual Window *CreateWindow() = 0;
	};
}
