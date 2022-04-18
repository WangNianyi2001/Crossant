#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

std::map<void *, Window *> Window::windowMap = std::map<void *, Window *>();

using Graphics::WindowEventType;
std::map<unsigned, WindowEventType> Window::eventMap = std::map<unsigned, WindowEventType>{
	{ WM_CLOSE, WindowEventType::Close }
};

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

long Window::ByPass(Legacy::Window::Event event) {
	return legacy->DefaultProcess(event);
}
