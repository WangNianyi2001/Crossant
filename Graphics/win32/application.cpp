#include "application.hpp"
#include <Windows.h>

using namespace Graphics::Win32;

Application::Application(Legacy::ModuleInstance *instance) :
	instance(instance) {
	Window::defaultClass = new Legacy::Window::Class(
		Legacy::Window::Class::Info{
			.process = &Window::MsgProc,
			.instance = instance,
			.className = Graphics::String(L"Window"),
		}
	);
}

Application::~Application() {
	delete instance;
}

#pragma push_macro("CreateWindow")
#undef CreateWindow
Window *Application::CreateWindow() {
	return new Window(this);
}
#pragma pop_macro("CreateWindow")

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	Application::current = new Application(
		new Legacy::ModuleInstance(hInst)
	);
	return Application::Main();
}
#pragma warning(pop)
