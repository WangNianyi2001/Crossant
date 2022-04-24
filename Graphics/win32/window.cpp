#include "window.hpp"
#include "graphicscontext/gdi.hpp"
#include <Windows.h>
#include <windowsx.h>

using namespace Graphics::Win32;
using Graphics::WindowEvent;
using LegacyWindow = Legacy::Window;
using Event = Legacy::Window::Event;
using Type = WindowEvent::Type;

std::map<void *, Window *> Window::windowMap{};

template<Type type>
WindowEvent directEvent(Event) {
	return WindowEvent{ type };
}

template<Type type>
WindowEvent mouseEvent(Event legacy) {
	WindowEvent event{ type };
	event.mouse = Graphics::Mouse{
		.position = {
			GET_X_LPARAM(legacy.l),
			GET_Y_LPARAM(legacy.l),
	}
	};
	return event;
}

WindowEvent resizeEvent(Event legacy) {
	Graphics::Vector2U size{
		LOWORD(legacy.l),
		HIWORD(legacy.l)
	};
	return WindowEvent{
		.type = Type::Resize,
		.clientSize = size
	};
}

std::map<
	unsigned,
	std::function<WindowEvent(Event)>
> Window::eventConversion{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_SIZE, &resizeEvent },
	{ WM_MOUSEMOVE, &mouseEvent<Type::MouseMove> },
	{ WM_LBUTTONDOWN, &mouseEvent<Type::MouseDown> },
	{ WM_LBUTTONUP, &mouseEvent<Type::MouseUp> },
	{ WM_RBUTTONDOWN, &mouseEvent<Type::MouseDown> },
	{ WM_RBUTTONUP, &mouseEvent<Type::MouseUp> },
	{ WM_PAINT, &directEvent<Type::Graph> },
};

__int64 __stdcall Window::MsgProc(void *hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam) {
	if(!windowMap.contains(hWnd))
		return DefWindowProc((HWND)hWnd, message, wParam, lParam);
	Window *window = windowMap[hWnd];
	if(!eventConversion.contains(message)) {
		return window->ByPass(
			Legacy::Window::Event(message, wParam, lParam)
		);
	}
	Legacy::Window::Event legacyEvent{
		message, wParam, lParam
	};
	window->Push(eventConversion[message](legacyEvent));
	return 0;
}

Window::Window(Legacy::Window *legacy) : legacy(legacy) {
	windowMap[legacy->handle] = this;
	alive = true;
}

Window::Window(Application *application) : Window(new Legacy::Window(Legacy::Window::CreationArguments{
	.windowClass = defaultClass,
	.instance = defaultClass->info.instance,
	})) {
}

__int64 Window::ByPass(Event event) {
	return legacy->DefProc(event);
}

bool Window::Alive() {
	return alive;
}

void Window::Live() {
	Push(WindowEvent(Type::Update));
	while(legacy->ProcessEvent());
}

void Window::Kill() {
	windowMap.erase(windowMap.find(legacy->handle));
	delete legacy;
	alive = false;
}

void Window::Show() {
	legacy->SetShowState(LegacyWindow::ShowState::Showdefault);
}

Graphics::GraphicsContext2D *Window::MakeGraphicsContext2D() {
	return new GDIContext(this);
}

Graphics::ScreenRect Window::ClientRect() {
	legacy->UpdateInfo();
	return legacy->info.clientRect;
}

void Window::Repaint() {
	legacy->UpdateClient();
}
