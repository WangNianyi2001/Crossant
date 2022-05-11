#pragma once

#include "Crossant/crossant.hpp"
#include "Crossant/feature/application.hpp"
#include "Win32/legacy.hpp"

namespace Crossant {
	struct Application::Impl {
		Legacy::Window::Class *windowClass;
		Legacy::ModuleInstance *instance;
	};

	__int64 __stdcall MsgProc(
		void *hWnd, unsigned int message,
		unsigned __int64 wParam, __int64 lParam
	);
}
