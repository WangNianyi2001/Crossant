#pragma once

#include "Graphics/feature/application.hpp"
#include "Win32/legacy.hpp"

namespace Graphics {
	struct Application::Impl {
		Legacy::Window::Class *windowClass;
		Legacy::ModuleInstance *instance;
	};

	static __int64 __stdcall MsgProc(
		void *hWnd, unsigned int message,
		unsigned __int64 wParam, __int64 lParam
	);
}
