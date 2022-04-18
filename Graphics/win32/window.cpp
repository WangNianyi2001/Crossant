#include "window.hpp"

using namespace Graphics::Win32;

std::map<void *, Window *> Window::windowMap = std::map<void *, Window *>();

Window::Window(Legacy::Window::CreationArguments arguments) :
	legacy(new Legacy::Window(arguments)) {
	windowMap[legacy->handle] = this;
}

Window::~Window() {
	windowMap.erase(windowMap.find(this));
}

void Window::Quit() {
	legacy->Quit();
}

void Window::Solo() {
	legacy->Run();
}

__int64 Window::ByPass(Legacy::Window::Event event) {
	return legacy->DefWindowProc(event);
}
