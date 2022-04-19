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

bool Window::ProcessEvent(Message min, Message max) {
	MSG msg;
	if(!PeekMessage(&msg, GetHandle<HWND>(), 0, 0, true))
		return false;
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return true;
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

void Window::ValidateClient() {
	ValidateRect(GetHandle<HWND>(), NULL);
}
