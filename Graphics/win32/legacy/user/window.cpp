#include "window.hpp"
#include "../gdi.hpp"
#include <Windows.h>

using namespace Graphics::Win32::Legacy;
using Class = Window::Class;

ATOM RegisterClass(Class::Info info) {
	WNDCLASSEX classEx;
	classEx.cbSize = sizeof(WNDCLASSEX);
	classEx.style = (UINT)info.style;
	classEx.lpfnWndProc = (WNDPROC)info.process;
	classEx.cbClsExtra = 0;
	classEx.cbWndExtra = 0;
	classEx.hInstance = info.instance->GetHandle<HINSTANCE>();
	classEx.hIcon = info.icon->GetHandle<HICON>();
	classEx.hCursor = info.cursor->GetHandle<HCURSOR>();
	classEx.hbrBackground = info.brush->GetHandle<HBRUSH>();
	classEx.lpszMenuName = info.menuName.c_str();
	classEx.lpszClassName = info.className.c_str();
	classEx.hIconSm = info.smallIcon->GetHandle<HICON>();
	ATOM classId = RegisterClassEx(&classEx);
	if(!classId)
		TryThrowLastError();
	return classId;
}

Class::Class(Info info) : info(info), id(RegisterClass(info)) {}

Window::Class::~Class() {
	if(!UnregisterClass((LPCWSTR)id, info.instance->GetHandle<HINSTANCE>()))
		TryThrowLastError();
}

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

void Window::UpdateInfo() {
	WINDOWINFO legacy{};
	GetWindowInfo(GetHandle<HWND>(), &legacy);
	info.windowRect = {
		{ legacy.rcWindow.left, legacy.rcWindow.top },
		{ legacy.rcWindow.right, legacy.rcWindow.bottom },
	};
	info.clientRect = {
		{ legacy.rcClient.left, legacy.rcClient.top },
		{ legacy.rcClient.right, legacy.rcClient.bottom },
	};
	info.style = (Style)legacy.dwStyle;
	info.extendedStyle = (ExtendedStyle)legacy.dwExStyle;
	info.active = (bool)legacy.dwWindowStatus;
	info.borderSize = Vector2U{ legacy.cxWindowBorders, legacy.cyWindowBorders };
}

void Window::BeginPaint(PaintStruct *paintStruct) {
	::BeginPaint(GetHandle<HWND>(), (LPPAINTSTRUCT)paintStruct->ps);
}

void Window::EndPaint(PaintStruct *paintStruct) {
	::EndPaint(GetHandle<HWND>(), (LPPAINTSTRUCT)paintStruct->ps);
}

void Window::UpdateClient() {
	InvalidateRect(GetHandle<HWND>(), NULL, false);
	//UpdateWindow(GetHandle<HWND>());
}
