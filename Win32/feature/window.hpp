#pragma once

#include "Crossant/feature/window.hpp"
#include "Win32/legacy.hpp"
#include <Windows.h>
#include <windowsx.h>
#include <map>

#ifdef CreateWindow
#pragma push_macro("CreateWindow")
#undef CreateWindow
#endif

namespace Crossant {
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
