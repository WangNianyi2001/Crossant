#include "application.hpp"
#include "window.hpp"

using namespace Crossant;

Application::Application() {
	impl = new Impl();
}

Application::~Application() {
	delete impl->instance;
	delete impl;
}

Window *Application::CreateWindow() {
	Window *window = new Window(*this);
	HWND hWnd = window->impl->legacy->GetHandle<HWND>();
	return Window::Impl::map[hWnd] = window;
}

__int64 __stdcall Crossant::MsgProc(
	void *hWnd, unsigned int message,
	unsigned __int64 wParam, __int64 lParam
) {
	if(!Window::Impl::map.contains(hWnd))
		return DefWindowProc((HWND)hWnd, message, wParam, lParam);
	Window *window = Window::Impl::map[hWnd];
	if(!Window::Impl::conversion.contains(message)) {
		Legacy::Window::Event legacy(message, wParam, lParam);
		return window->impl->legacy->DefProc(legacy);
	}
	Legacy::Window::Event legacyEvent{
		message, wParam, lParam
	};
	auto convert = Window::Impl::conversion[message];
	window->Push(convert(legacyEvent));
	return 0;
}

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	Application::current = new Application();
	Application::Impl *impl = Application::current->impl;
	impl->instance = new Legacy::ModuleInstance(hInst);
	impl->windowClass = new Legacy::Window::Class(
		Legacy::Window::Class::Info{
			.process = &MsgProc,
			.instance = impl->instance,
			.className = String(L"Window"),
		}
	);
	return Application::Main();
}
#pragma warning(pop)
