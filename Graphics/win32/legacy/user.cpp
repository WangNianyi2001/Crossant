#include "user.hpp"
#include <Windows.h>

#define GET_HANDLE(type, obj) (\
	obj == nullptr ? NULL :\
	reinterpret_cast<type>((obj)->handle)\
)

using namespace Graphics::Win32::Legacy;

WindowClass *WindowClass::Register(Info info) {
	WNDCLASSEX classEx;
	classEx.cbSize = sizeof(WNDCLASSEX);
	classEx.style = (UINT)info.style;
	classEx.lpfnWndProc = (WNDPROC)info.process;
	classEx.cbClsExtra = 0;
	classEx.cbWndExtra = 0;
	classEx.hInstance = GET_HANDLE(HINSTANCE, info.instance);
	classEx.hIcon = GET_HANDLE(HICON, info.icon);
	classEx.hCursor = GET_HANDLE(HCURSOR, info.cursor);
	classEx.hbrBackground = GET_HANDLE(HBRUSH, info.brush);
	classEx.lpszMenuName = info.menuName.c_str();
	classEx.lpszClassName = info.className.c_str();
	classEx.hIconSm = GET_HANDLE(HICON, info.smallIcon);
	ATOM classId = RegisterClassEx(&classEx);
	if(!classId)
		TryThrowLastError();
	WindowClass *windowClass = new WindowClass(classId, info);
	return windowClass;
}

void WindowClass::Unregister() {
	if(!UnregisterClass((LPCWSTR)id, GET_HANDLE(HINSTANCE, info.instance)))
		TryThrowLastError();
}

Window::~Window() {
	if(!handle)
		return;
	if(DestroyWindow((HWND)handle))
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
	GET_HANDLE(HWND, arguments.parent),
	GET_HANDLE(HMENU, arguments.menu),
	GET_HANDLE(HINSTANCE, arguments.instance),
	NULL
)) {}

void Window::Run() {
	ShowWindow(GET_HANDLE(HWND, this), SW_SHOWDEFAULT);
	UpdateWindow(GET_HANDLE(HWND, this));
	for(MSG msg; ; ) {
		if(!PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			break;
	}
}

long Window::DefaultProcess(Event event) {
	return DefWindowProc(GET_HANDLE(HWND, this), event.type, event.w, event.l);
}

void Window::Quit() {
	return PostQuitMessage(0);
}
