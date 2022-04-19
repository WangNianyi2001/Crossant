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
	if(DestroyWindow(GetHandle<HWND>()))
		TryThrowLastError();
}

Window::Event Window::GetEvent(bool remove, Message min, Message max) {
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	Event event(
		msg.message, msg.wParam, msg.lParam,
		msg.time, msg.pt.x, msg.pt.y
	);
	return event;
}

Window::L Window::DispatchEvent(Event event) {
	MSG msg{
		.hwnd = GetHandle<HWND>(),
		.message = event.type,
		.wParam = event.w,
		.lParam = event.l,
		.time = event.time,
		.pt = POINT{ event.x, event.y }
	};
	return DispatchMessage(&msg);
}

Window::L Window::DefProc(Event event) {
	return DefWindowProc(GetHandle<HWND>(), event.type, event.w, event.l);
}

void Window::SetShowState(ShowState state) {
	ShowWindow(GetHandle<HWND>(), (int)state);
}

void Window::UpdateClient() {
	UpdateWindow(GetHandle<HWND>());
}
