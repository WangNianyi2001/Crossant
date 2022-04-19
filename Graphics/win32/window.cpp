#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

std::map<void *, Window *> Window::windowMap{};

template<Graphics::WindowEvent::Type type>
Graphics::WindowEvent directEvent(Legacy::Window::Event) {
	Graphics::WindowEvent event;
	event.type = type;
	return event;
}

std::map<
	unsigned,
	std::function<Graphics::WindowEvent(Legacy::Window::Event)>
> Window::eventConversion{
	{ WM_PAINT, &directEvent<WindowEvent::Type::Paint> },
	{ WM_CLOSE, &directEvent<WindowEvent::Type::Close> }
};

Window::Window(Legacy::Window::CreationArguments arguments) :
	legacy(new Legacy::Window(arguments)) {
	windowMap[legacy->handle] = this;
	alive = true;
}

__int64 Window::ByPass(Legacy::Window::Event event) {
	return legacy->DefProc(event);
}

bool Window::Alive() {
	return alive;
}

void Window::Live() {
	for(Push(WindowEvent(WindowEvent::Type::Update));
		legacy->ProcessEvent();
		);
}

void Window::Destroy() {
	windowMap.erase(windowMap.find(legacy->handle));
	delete legacy;
	alive = false;
}

void Window::Show() {
	legacy->SetShowState(Legacy::Window::ShowState::Showdefault);
}
