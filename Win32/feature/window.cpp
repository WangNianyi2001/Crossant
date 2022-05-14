#include "window.hpp"
#include "graphics/target.hpp"

using namespace Crossant;

__int64 __stdcall MsgProc(
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
	window->Push(convert(window, legacyEvent));
	return 0;
}

#pragma warning(push)
#pragma warning(disable: 28251)
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	instance = new Legacy::ModuleInstance(hInst);
	windowClass = new Legacy::Window::Class(
		Legacy::Window::Class::Info{
			.process = &MsgProc,
			.instance = instance,
			.className = String(L"Window"),
		}
	);
	return Main();
}
#pragma warning(pop)

using LegacyEvent = Legacy::Window::Event;
using Type = Window::Event::Type;

template<Type type>
Window::Event directEvent(Window * window, LegacyEvent) {
	return Window::Event{ window, type };
}

template<Type type>
Window::Event mouseEvent(Window *window, LegacyEvent legacy) {
	Window::Event event = directEvent<type>(window, LegacyEvent {});
	window->mouse.position = {
		(Float)GET_X_LPARAM(legacy.l),
		(Float)GET_Y_LPARAM(legacy.l),
	};
	return event;
}

using MB = Mouse::Button;

template<Type type, MB button, bool clicked>
Window::Event mouseButtonEvent(Window *window, LegacyEvent legacy) {
	window->mouse.buttons[button] = clicked;
	Window::Event event = mouseEvent<type>(window, legacy);
	event.mouseButton = button;
	return event;
}

std::map<void *, Window *> Window::Impl::map{};

std::map<
	unsigned,
	std::function<Window::Event(Window *, LegacyEvent)>
> Window::Impl::conversion{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_SIZE, [](Window *window, LegacyEvent) {
		delete window->graphicsTarget.impl;
		HDC hdc = GetDC(window->impl->legacy->GetHandle<HWND>());
		auto dc = new Legacy::DeviceContext(hdc);
		auto size = (Size2D)window->ClientRect().Diagonal();
		window->graphicsTarget.impl = new Graphics::Target::Impl(*dc, size);
		return Window::Event{ window, Type::Resize };
	} },
	{ WM_MOUSEMOVE, &mouseEvent<Type::MouseMove> },
	{ WM_LBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Left, true> },
	{ WM_LBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Left, false> },
	{ WM_RBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Right, true> },
	{ WM_RBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Right, false> },
	{ WM_MBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Middle, true> },
	{ WM_MBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Middle, false> },
	{ WM_PAINT, [](Window *window, LegacyEvent) {
		window->impl->legacy->Validate();
		return Window::Event{ window, Type::Draw };
	}},
};

Window::Window() {
	impl = new Window::Impl{
		.legacy = new Legacy::Window({
			.windowClass = windowClass,
			.instance = windowClass->info.instance,
		}),
		.alive = true
	};
	Impl::map[impl->legacy->handle] = this;
}

Window::~Window() {
	delete impl;
}

bool Window::Alive() {
	return impl->alive;
}

void Window::Live() {
	Push(Window::Event{ this, Type::Update });
	while(impl->legacy->ProcessEvent());
}

void Window::Kill() {
	Impl::map.erase(Impl::map.find(impl->legacy->handle));
	delete impl->legacy;
	impl->alive = false;
}

void Window::Show() {
	impl->legacy->SetShowState(Legacy::Window::ShowState::Default);
}

RectRange Window::ClientRect() {
	impl->legacy->UpdateInfo();
	return impl->legacy->info.clientRect;
}

void Window::Repaint() {
	impl->legacy->Invalidate();
}
