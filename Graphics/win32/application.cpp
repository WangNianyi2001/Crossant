#include "application.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	auto it = Window::windowMap.find(hWnd);
	if(it == Window::windowMap.end())
		return DefWindowProc(hWnd, message, wParam, lParam);
	Window *window = it->second;
	if(Window::eventMap.find(message) != Window::eventMap.end()) {
		Legacy::Window::Event bypass;
		bypass.type = message;
		bypass.w = wParam;
		bypass.l = lParam;
		return window->ByPass(bypass);
	}
	Graphics::WindowEvent event;
	event.type = Window::eventMap[message];
	window->Fire(event);
	return 0;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#undef CreateWindow
Window *Application::CreateWindow() {
	Legacy::Window::CreationArguments arguments{};
	arguments.instance = instance;
	arguments.windowClass = defaultWindowClass;
	return new Window(arguments);
}

Application::Application(Legacy::ModuleInstance *instance) :
	instance(instance) {
	Legacy::WindowClass::Info info{
		.process = &MsgProc,
		.instance = instance,
		.className = Legacy::String(L"Window"),
	};
	defaultWindowClass = Legacy::WindowClass::Register(info);
}

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	auto *instance = new Legacy::ModuleInstance(hInst);
	Application::current = new Application(instance);
	return Application::Main();
}
#pragma warning(pop)
