#include "window.hpp"
#include "../gdi.hpp"
#include <Windows.h>

using namespace Crossant::Legacy;
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
)) {}

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

using WS = Window::ShowState;
std::map<WS, int> showStateMap{
	{ WS::Hidden, SW_HIDE },
	{ WS::Normal, SW_NORMAL },
	{ WS::Minimized, SW_MINIMIZE },
	{ WS::Maximized, SW_MAXIMIZE },
	{ WS::Restore, SW_RESTORE },
	{ WS::Default, SW_SHOWDEFAULT },
};
void Window::SetShowState(ShowState state) {
	ShowWindow(GetHandle<HWND>(), showStateMap[state]);
}

inline Crossant::RectRange ParseRect(RECT rect) {
	using Crossant::Float;
	return {
		{ (Float)rect.left, (Float)rect.top },
		{ (Float)rect.right, (Float)rect.bottom }
	};
}

void Window::UpdateInfo() {
	WINDOWINFO legacy{
		.cbSize = sizeof(WINDOWINFO)
	};
	GetWindowInfo(GetHandle<HWND>(), &legacy);
	info.windowRect = ParseRect(legacy.rcWindow);
	info.clientRect = ParseRect(legacy.rcClient);
	info.style = (Style)legacy.dwStyle;
	info.extendedStyle = (ExtendedStyle)legacy.dwExStyle;
	info.active = (bool)legacy.dwWindowStatus;
	info.borderSize = Size2D{ legacy.cxWindowBorders, legacy.cyWindowBorders };
}

void Window::SetCursorPos(Coord2D offset) {
	::SetCursorPos((int)offset[0], (int)offset[1]);
}

void Window::BeginPaint(PaintStruct *paintStruct) {
	::BeginPaint(GetHandle<HWND>(), (LPPAINTSTRUCT)paintStruct->ps);
}

void Window::EndPaint(PaintStruct *paintStruct) {
	::EndPaint(GetHandle<HWND>(), (LPPAINTSTRUCT)paintStruct->ps);
}

void Window::Invalidate() {
	InvalidateRect(GetHandle<HWND>(), NULL, false);
}

void Window::Validate() {
	ValidateRect(GetHandle<HWND>(), NULL);
}
