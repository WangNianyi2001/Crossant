#include "application.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

LRESULT WINAPI MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if(!Window::windowMap.contains(hWnd))
		return DefWindowProc(hWnd, message, wParam, lParam);
	Window *window = Window::windowMap[hWnd];
	if(!Window::eventConversion.contains(message)) {
		return window->ByPass(
			Legacy::Window::Event(message, wParam, lParam)
		);
	}
	Legacy::Window::Event legacyEvent{
		message, wParam, lParam
	};
	window->Push(Window::eventConversion[message](legacyEvent));
	return 0;
}

Application::Application(Legacy::ModuleInstance *instance) :
	instance(instance),
	defaultWindowClass(new Legacy::Window::Class(
		{
			.process = &MsgProc,
			.instance = instance,
			.className = Legacy::String(L"Window"),
		})) {
}

Application::~Application() {
	delete defaultWindowClass;
	delete instance;
}

#pragma push_macro("CreateWindow")
#undef CreateWindow
Window *Application::CreateWindow() {
	Legacy::Window::CreationArguments arguments{};
	arguments.instance = instance;
	arguments.windowClass = defaultWindowClass;
	auto *legacy = new Legacy::Window(arguments);
	return new Window(this, legacy);
}
#pragma pop_macro("CreateWindow")

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	auto *instance = new Legacy::ModuleInstance(hInst);
	Application::current = new Application(instance);
	return Application::Main();
}
#pragma warning(pop)
