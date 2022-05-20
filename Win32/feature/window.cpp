#include "window.hpp"
#include "graphics/target.hpp"
#include "keyboard.hpp"
#include <shellapi.h>

using namespace Crossant;

std::map<void *, Window *> Window::Impl::windowMap{};

LRESULT __stdcall MsgProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
) {
	using Impl = Window::Impl;
	if(!Impl::windowMap.contains(hWnd))
		return DefWindowProc((HWND)hWnd, message, wParam, lParam);
	Window *window = Impl::windowMap[hWnd];
	if(Impl::eventConversionMap.contains(message)) {
		auto convert = Impl::eventConversionMap[message];
		auto event = convert(window, message, wParam, lParam);
		window->Push(event);
	}
	return DefWindowProc(window->impl->hWnd, message, wParam, lParam);
}

int Crossant::argc;
Char **Crossant::argv;

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	argv = CommandLineToArgvW(GetCommandLine(), &argc);
	hInstance = hInst;
	WNDCLASSEX classDescriptor{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_CLASSDC,
		.lpfnWndProc = &MsgProc,
		.hInstance = hInst,
		.hIcon = NULL,
		.hCursor = NULL,
		.hbrBackground = NULL,
		.lpszMenuName = TEXT(""),
		.lpszClassName = TEXT("Window"),
		.hIconSm = NULL,
	};
	windowClass = RegisterClassEx(&classDescriptor);
	return Main();
}
#pragma warning(pop)

void CentralizeCursor(Window &window) {
	auto clientSize = window.ClientRect().Diagonal();
	Vector<int, 2> clientPos = clientSize / 2;
	POINT point{ (LONG)clientPos[0], (LONG)clientPos[1] };
	ClientToScreen(window.impl->hWnd, &point);
	SetCursorPos(point.x, point.y);
	Mouse::offset = clientPos;
}

using Type = Window::Event::Type;

template<Type type>
Window::Event directEvent(Window *window, UINT = NULL, WPARAM = NULL, LPARAM = NULL) {
	return Window::Event{ window, type };
}

using MB = Mouse::Button;

template<Type type, MB button>
Window::Event mouseButtonEvent(Window *window,
	UINT message, WPARAM wParam, LPARAM lParam
) {
	Window::Event event = directEvent<type>(window, message, wParam, lParam);
	event.mouseButton = button;
	return event;
}

template<Type type>
Window::Event keyboardEvent(Window *window,
	UINT message, WPARAM wParam, LPARAM lParam
) {
	Window::Event event = directEvent<type>(window, message, wParam, lParam);
	event.key = VKToKey((Byte)wParam);
	return event;
}

std::map<unsigned, Window::Impl::LegacyProcessor>
Window::Impl::eventConversionMap{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_SIZE, [](Window *window, UINT, WPARAM, LPARAM) {
		ReleaseDC(window->impl->hWnd, window->graphicsTarget.impl->hDC);
		delete window->graphicsTarget.impl;
		window->graphicsTarget.impl = new Graphics::Target::Impl(
			GetDC(window->impl->hWnd),
			(Size2D)window->ClientRect().Diagonal()
		);
		return Window::Event{ window, Type::Resize };
	} },
	{ WM_MOUSEMOVE, [](Window *window, UINT, WPARAM, LPARAM lParam) {
		Window::Event event = directEvent<Type::MouseMove>(window);
		Coord2D offset = {
			(Float)GET_X_LPARAM(lParam),
			(Float)GET_Y_LPARAM(lParam),
		};
		Mouse::deltaPosition = offset - Mouse::offset;
		if(window->impl->cursorLocked)
			CentralizeCursor(*window);
		else
			Mouse::offset = offset;
		return event;
	}},
	{ WM_LBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Left> },
	{ WM_LBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Left> },
	{ WM_RBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Right> },
	{ WM_RBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Right> },
	{ WM_MBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Middle> },
	{ WM_MBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Middle> },
	{ WM_KEYDOWN, &keyboardEvent<Type::KeyDown> },
	{ WM_KEYUP, &keyboardEvent<Type::KeyUp> },
	{ WM_PAINT, [](Window *window, UINT, WPARAM, LPARAM) {
		ValidateRect(window->impl->hWnd, NULL);
		return Window::Event{ window, Type::Draw };
	}},
};

Window::Window() : impl(new Window::Impl{
	.hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		(LPTSTR)windowClass,
		TEXT(""),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	)
}), graphicsTarget(new Graphics::Target::Impl(GetDC(impl->hWnd), Size2D{ 1, 1 })) {
	Impl::windowMap[impl->hWnd] = this;
}

Window::~Window() {
	delete impl;
}

bool Window::Alive() {
	return impl->hWnd != NULL && impl->alive;
}

void Window::Live() {
	while(true) {
		MSG msg;
		if(!PeekMessage(&msg, impl->hWnd, 0, 0, true))
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Mouse::deltaPosition = Coord2D{};
	Push(Window::Event{ this, Type::Update });
}

void Window::Kill() {
	if(Impl::windowMap.contains(impl->hWnd))
		Impl::windowMap.erase(Impl::windowMap.find(impl->hWnd));
	DestroyWindow(impl->hWnd);
	impl->alive = false;
}

void Window::Show() {
	ShowWindow(impl->hWnd, SW_SHOWDEFAULT);
}

void Window::SetCursorLockState(bool locked) {
	if(locked && !impl->cursorLocked)
		CentralizeCursor(*this);
	impl->cursorLocked = locked;
}

inline RectRange ParseRect(RECT rect) {
	return {
		{ (Float)rect.left, (Float)rect.top },
		{ (Float)rect.right, (Float)rect.bottom }
	};
}

RectRange Window::ClientRect() {
	WINDOWINFO info{
		.cbSize = sizeof(WINDOWINFO)
	};
	GetWindowInfo(impl->hWnd, &info);
	return ParseRect(info.rcClient);
}

void Window::Repaint() {
	InvalidateRect(impl->hWnd, NULL, false);
}
