#include "application.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if(!Window::windowMap.contains(hWnd))
		return DefWindowProc(hWnd, message, wParam, lParam);
	Window *window = Window::windowMap[hWnd];
	if(!Window::eventMap.contains(message)) {
		return window->ByPass(
			Legacy::Window::Event(message, wParam, lParam)
		);
	}
	Graphics::WindowEvent event;
	event.type = Window::eventMap[message];
	window->Fire(event);
	return 0;
}

Application::Application(Legacy::ModuleInstance *instance) :
	instance(instance),
	defaultWindowClass(new Legacy::WindowClass(
		{
			.process = &MsgProc,
			.instance = instance,
			.className = Legacy::String(L"Window"),
		})) {
}

#pragma push_macro(CreateWindow)
#undef CreateWindow
Window *Application::CreateWindow() {
	Legacy::Window::CreationArguments arguments{};
	arguments.instance = instance;
	arguments.windowClass = defaultWindowClass;
	return new Window(arguments);
}
#pragma pop_macro(CreateWindow)

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	auto *instance = new Legacy::ModuleInstance(hInst);
	Application::current = new Application(instance);
	return Application::Main();
}
#pragma warning(pop)
