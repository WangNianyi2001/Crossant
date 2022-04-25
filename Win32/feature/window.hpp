#pragma once

#include <map>
#include "Graphics/graphics.hpp"
#include "../legacy.hpp"
#include <Windows.h>
#include <windowsx.h>

namespace Graphics {
	using Event = Legacy::Window::Event;
	using Type = WindowEvent::Type;

	struct Window::Impl {
		static std::map<void *, Window *> map;

		static std::map<
			unsigned,
			std::function<WindowEvent(Event)>
		> conversion;

		Legacy::Window *const legacy;
		bool alive;
	};
}
