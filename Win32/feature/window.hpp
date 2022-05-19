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
	static HINSTANCE hInstance;
	static ATOM windowClass;

	struct Window::Impl {
		static std::map<void *, Window *> windowMap;

		using LegacyProcessor = std::function<Event(
			Window *, UINT, WPARAM, LPARAM
		)>;
		static std::map<unsigned, LegacyProcessor> eventConversionMap;

		HWND hWnd;
		bool alive = true;
		bool cursorLocked = false;
	};
}
