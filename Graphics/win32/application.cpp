#include "application.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

static std::map<void *, Window *> windowMap = std::map<void *, Window *>();

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	auto it = windowMap.find(hWnd);
	if(it == windowMap.end())
		return DefWindowProc(hWnd, message, wParam, lParam);
	Window *window = it->second;
	Window::Event event;
	event.type = message;
	event.w = wParam;
	event.l = lParam;
	if(!window->Fire(event))
		return window->DefaultProcess(event);
	return 0;
}

Application *Application::current = nullptr;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#undef CreateWindow
Window *Application::CreateWindow(Window::CreationArguments arguments) {
	arguments.instance = instance;
	arguments.windowClass = defaultWindowClass;
	Window *window = new Window(arguments);
	windowMap[window->handle] = window;
	return window;
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
	Application* current = Application::current =
		new Application(new Legacy::ModuleInstance(hInst));
	return Application::Main();
}
#pragma warning(pop)
