#pragma once

#include "../event.hpp"
#include "legacy/user.hpp"
#include <map>

namespace Graphics::Win32 {
	class Window :
		public Legacy::Window,
		public EventDistributor<long, Legacy::Window::Event> {
	public:
		using Event = Legacy::Window::Event;

		Window(Legacy::Window::CreationArguments arguments) :
			Legacy::Window(arguments) {}
	};
}
