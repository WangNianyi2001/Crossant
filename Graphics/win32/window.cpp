#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

std::map<void *, Window *> Window::windowMap{};

std::map<unsigned, Graphics::WindowEventType> Window::eventMap{
	{ WM_CLOSE, WindowEventType::Close }
};

Window::Window(Legacy::Window::CreationArguments arguments) :
	legacy(new Legacy::Window(arguments)) {
	windowMap[legacy->handle] = this;
	alive = true;
}

__int64 Window::ByPass(Legacy::Window::Event event) {
	return legacy->DefProc(event);
}

void Window::Show() {
	legacy->SetShowState(Legacy::Window::ShowState::Showdefault);
}

bool Window::Alive() {
	return alive;
}

void Window::Live() {
	Legacy::Window::Event event = legacy->GetEvent();
	legacy->DispatchEvent(event);
}

void Window::Destroy() {
	windowMap.erase(windowMap.find(legacy->handle));
	delete legacy;
	alive = false;
}
