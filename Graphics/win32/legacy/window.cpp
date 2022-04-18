#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;

Window::Window(CreationArguments arguments) : Window(CreateWindowEx(
	(DWORD)arguments.extendedStyle,
	(LPCWSTR)arguments.windowClass->id,
	arguments.windowName.c_str(),
	(DWORD)arguments.style,
	arguments.x,
	arguments.y,
	arguments.width,
	arguments.height,
	arguments.parent->GetHandle<HWND>(),
	arguments.menu->GetHandle<HMENU>(),
	arguments.instance->GetHandle<HINSTANCE>(),
	NULL
)) {
}

Window::~Window() {
	if(!handle)
		return;
	if(DestroyWindow((HWND)handle))
		TryThrowLastError();
}

void Window::Run() {
	ShowWindow(GetHandle<HWND>(), SW_SHOWDEFAULT);
	UpdateWindow(GetHandle<HWND>());
	for(MSG msg; ; ) {
		if(!PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			break;
	}
}

__int64 Window::DefaultProcess(Event event) {
	return DefWindowProc(GetHandle<HWND>(), event.type, event.w, event.l);
}

void Window::Quit() {
	return PostQuitMessage(0);
}
