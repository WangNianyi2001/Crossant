#include "window.hpp"
#include "application.hpp"
#include "graphics/target.hpp"

using namespace Crossant;

using Event = Legacy::Window::Event;
using Type = WindowEvent::Type;

template<Type type>
WindowEvent directEvent(Window *window, Event) {
	return WindowEvent{ window, type };
}

template<Type type>
WindowEvent mouseEvent(Window *window, Event legacy) {
	WindowEvent event = directEvent<type>(window, Event {});
	window->mouse.position = {
		(Float)GET_X_LPARAM(legacy.l),
		(Float)GET_Y_LPARAM(legacy.l),
	};
	return event;
}

using MB = Mouse::Button;

template<Type type, MB button, bool clicked>
WindowEvent mouseButtonEvent(Window *window, Event legacy) {
	window->mouse.buttons[button] = clicked;
	WindowEvent event = mouseEvent<type>(window, legacy);
	event.mouseButton = button;
	return event;
}

std::map<void *, Window *> Window::Impl::map{};

std::map<
	unsigned,
	std::function<WindowEvent(Window *, Event)>
> Window::Impl::conversion{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_SIZE, &directEvent<Type::Resize> },
	{ WM_MOUSEMOVE, &mouseEvent<Type::MouseMove> },
	{ WM_LBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Left, true> },
	{ WM_LBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Left, false> },
	{ WM_RBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Right, true> },
	{ WM_RBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Right, false> },
	{ WM_MBUTTONDOWN, &mouseButtonEvent<Type::MouseDown, MB::Middle, true> },
	{ WM_MBUTTONUP, &mouseButtonEvent<Type::MouseUp, MB::Middle, false> },
	{ WM_PAINT, &directEvent<Type::Draw> },
};


static Window::Impl *makeImpl(Application &application) {
	auto windowClass = application.impl->windowClass;
	return new Window::Impl{
		.legacy = new Legacy::Window({
			.windowClass = windowClass,
			.instance = windowClass->info.instance,
		}),
		.alive = true
	};
}

static Graphics::Target::Impl *makeTargetImpl(Window &window) {
	auto hdc = GetDC(window.impl->legacy->GetHandle<HWND>());
	auto dc = new Legacy::DeviceContext(hdc);
	auto size = (Size2D)window.ClientRect().Diagonal();
	return new Graphics::Target::Impl(*dc, size);
}

Window::Window(Application &application) :
	impl(makeImpl(application)),
	graphicsTarget{ makeTargetImpl(*this) } {
	Impl::map[impl->legacy->handle] = this;
	Listen(Type::Draw, [&](WindowEvent) {
		impl->legacy->Validate();
	});
}

Window::~Window() {
	delete impl;
}

bool Window::Alive() {
	return impl->alive;
}

void Window::Live() {
	Push(WindowEvent{ this, Type::Update });
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
