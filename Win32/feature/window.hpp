#pragma once

#include "Graphics/graphics.hpp"
#include "Win32/legacy.hpp"
#include <Windows.h>
#include <windowsx.h>
#include <map>

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
