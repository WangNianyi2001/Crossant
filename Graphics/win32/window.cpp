#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

struct Window::Impl {
	HWND hWnd;
	HDC hDC;
};

static HINSTANCE hInst;

void Window::Miss(WindowEvent event) {
	DefWindowProc(impl->hWnd, event.type, event.w, event.l);
}

void Window::Run() {
	ShowWindow(impl->hWnd, SW_SHOWDEFAULT);
	UpdateWindow(impl->hWnd);
	for(MSG msg; ; ) {
		if(!PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			break;
	}
}

void Window::Stop() {
	return PostQuitMessage(0);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if(!Window::Created())
		return DefWindowProc(hWnd, message, wParam, lParam);
	WindowEvent event;
	event.type = message;
	event.w = wParam;
	event.l = lParam;
	try {
		Window::Create()->Fire(event);
	} catch(LRESULT e) {
		return e;
	}
	return 0;
}

Window *Window::Create() {
	if(Created())
		return main;

	int iw = 800, ih = 600;
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int nX = (w - iw) / 2, nY = (h - ih) / 2;

	auto window_class_name = TEXT("Window");
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		window_class_name, NULL
	};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowEx(NULL,
		window_class_name,
		TEXT("Window Title"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		nX, nY, iw, ih,
		NULL, NULL, hInst, NULL);

	Window *window = new Window();
	Impl *impl = window->impl = new Impl();
	impl->hWnd = hWnd;
	impl->hDC = GetDC(hWnd);
	return main = window;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	::hInst = hInst;
	return Main();
}
