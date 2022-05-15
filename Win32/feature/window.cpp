#include "window.hpp"
#include "graphics/target.hpp"
#include "keyboard.hpp"

using namespace Crossant;

__int64 __stdcall MsgProc(
	void *hWnd, unsigned int message,
	unsigned __int64 wParam, __int64 lParam
) {
	if(!Window::Impl::map.contains(hWnd))
		return DefWindowProc((HWND)hWnd, message, wParam, lParam);
	Window *window = Window::Impl::map[hWnd];
	if(Window::Impl::conversion.contains(message)) {
		Legacy::Window::Event legacyEvent{
			message, wParam, lParam
		};
		auto convert = Window::Impl::conversion[message];
		window->Push(convert(window, legacyEvent));
	}
	Legacy::Window::Event legacy(message, wParam, lParam);
	return window->impl->legacy->DefProc(legacy);
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

void CentralizeCursor(Window &window) {
	Legacy::Window *const legacy = window.impl->legacy;
	auto clientSize = legacy->info.clientRect.Diagonal();
	Vector<int, 2> clientPos = clientSize / 2;
	POINT point{ (LONG)clientPos[0], (LONG)clientPos[1] };
	ClientToScreen(legacy->GetHandle<HWND>(), &point);
	Vector<int, 2> screenPos{ point.x, point.y };
	legacy->SetCursorPos(screenPos);
	Mouse::position = clientPos;
}

using LegacyEvent = Legacy::Window::Event;
using Type = Window::Event::Type;

template<Type type>
Window::Event directEvent(Window * window, LegacyEvent) {
	return Window::Event{ window, type };
}

using MB = Mouse::Button;

template<Type type, MB button>
Window::Event mouseButtonEvent(Window *window, LegacyEvent legacy) {
	Window::Event event = directEvent<type>(window, legacy);
	event.mouseButton = button;
	return event;
}

template<Type type>
Window::Event keyboardEvent(Window *window, LegacyEvent legacy) {
	Window::Event event = directEvent<type>(window, legacy);
	event.key = VKToKey((Byte)legacy.w);
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
	{ WM_MOUSEMOVE, [](Window *window, LegacyEvent legacy) {
		Window::Event event = directEvent<Type::MouseMove>(window, LegacyEvent {});
		Coord2D position = {
			(Float)GET_X_LPARAM(legacy.l),
			(Float)GET_Y_LPARAM(legacy.l),
		};
		Mouse::deltaPosition = position - Mouse::position;
		if(window->impl->cursorLocked)
			CentralizeCursor(*window);
		else
			Mouse::position = position;
		return event;
	}},
	{ WM_LBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Left> },
	{ WM_LBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Left> },
	{ WM_RBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Right> },
	{ WM_RBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Right> },
	{ WM_MBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Middle> },
	{ WM_MBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Middle> },
	{ WM_KEYDOWN, &keyboardEvent<Type::KeyDown> },
	{ WM_KEYUP, &keyboardEvent<Type::KeyUp> },
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
		})
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

void Window::SetCursorLockState(bool locked) {
	if(locked && !impl->cursorLocked)
		CentralizeCursor(*this);
	impl->cursorLocked = locked;
}

RectRange Window::ClientRect() {
	impl->legacy->UpdateInfo();
	return impl->legacy->info.clientRect;
}

void Window::Repaint() {
	impl->legacy->Invalidate();
}
