#include "window.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

std::map<void *, Window *> Window::windowMap{};

std::map<unsigned, Graphics::WindowEventType> Window::eventMap{
	{ WM_PAINT, WindowEventType::Paint },
	{ WM_CLOSE, WindowEventType::Close }
};

Window::Window(Legacy::Window::CreationArguments arguments) :
	legacy(new Legacy::Window(arguments)) {
	windowMap[legacy->handle] = this;
	alive = true;
	paintStruct = new PAINTSTRUCT;
}

__int64 Window::ByPass(Legacy::Window::Event event) {
	return legacy->DefProc(event);
}

bool Window::Alive() {
	return alive;
}

void Window::Live() {
	for(Push(WindowEvent(WindowEventType::Update));
		legacy->ProcessEvent();
		);
}

void Window::Destroy() {
	windowMap.erase(windowMap.find(legacy->handle));
	delete legacy;
	alive = false;
	delete paintStruct;
}

void Window::Show() {
	legacy->SetShowState(Legacy::Window::ShowState::Showdefault);
}

void Window::BeginPaint() {
	::BeginPaint(legacy->GetHandle<HWND>(), (PAINTSTRUCT *)paintStruct);
}

void Window::FinishPaint() {
	::EndPaint(legacy->GetHandle<HWND>(), (PAINTSTRUCT *)paintStruct);
}
