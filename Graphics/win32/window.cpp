#include "window.hpp"
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
WindowEvent mouseEvent(Event legacyEvent) {
	WindowEvent event{ type };
	event.mouse = Graphics::Mouse{
		.position = {
			GET_X_LPARAM(legacyEvent.l),
			GET_Y_LPARAM(legacyEvent.l),
		}
	};
	return event;
}

std::map<
	unsigned,
	std::function<WindowEvent(Event)>
> Window::eventConversion{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_LBUTTONDOWN, &mouseEvent<Type::MouseDown> },
	{ WM_LBUTTONUP, &mouseEvent<Type::MouseUp> },
	{ WM_PAINT, &directEvent<Type::Paint> },
};

Window::Window(Application *application, Legacy::Window *legacy) :
	application(application),
	legacy(legacy) {
	windowMap[legacy->handle] = this;
	alive = true;
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

void Window::Destroy() {
	windowMap.erase(windowMap.find(legacy->handle));
	delete legacy;
	alive = false;
}

void Window::Show() {
	legacy->SetShowState(LegacyWindow::ShowState::Showdefault);
}
