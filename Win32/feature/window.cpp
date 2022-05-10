#include "window.hpp"
#include "application.hpp"
#include "graphics/target.hpp"

using namespace Graphics;

template<Type type>
WindowEvent directEvent(Event) {
	return WindowEvent{ type };
}

template<Type type>
WindowEvent mouseEvent(Event legacy) {
	WindowEvent event{ type };
	event.mouse = Graphics::Mouse{
		.position = {
			(Float)GET_X_LPARAM(legacy.l),
			(Float)GET_Y_LPARAM(legacy.l),
		}
	};
	return event;
}

WindowEvent resizeEvent(Event legacy) {
	Graphics::Size2D size{
		LOWORD(legacy.l),
		HIWORD(legacy.l)
	};
	return WindowEvent{
		.type = Type::Resize,
		.clientSize = size
	};
}

std::map<void *, Window *> Window::Impl::map{};

std::map<
	unsigned,
	std::function<WindowEvent(Event)>
> Window::Impl::conversion{
	{ WM_CLOSE, &directEvent<Type::Close> },
	{ WM_SIZE, &resizeEvent },
	{ WM_MOUSEMOVE, &mouseEvent<Type::MouseMove> },
	{ WM_LBUTTONDOWN, &mouseEvent<Type::MouseDown> },
	{ WM_LBUTTONUP, &mouseEvent<Type::MouseUp> },
	{ WM_RBUTTONDOWN, &mouseEvent<Type::MouseDown> },
	{ WM_RBUTTONUP, &mouseEvent<Type::MouseUp> },
	{ WM_PAINT, &directEvent<Type::Paint> },
};

Window::Window(Application *application) :
	impl(new Impl{
		.legacy = new Legacy::Window({
			.windowClass = application->impl->windowClass,
			.instance = application->impl->windowClass->info.instance,
		}),
		.alive = true
	}),
	graphicsTarget{ new GraphicsTarget::Impl(
		*new Legacy::DeviceContext(GetDC(impl->legacy->GetHandle<HWND>())),
		(Size2D)ClientRect().Diagonal()
	) } {
	Impl::map[impl->legacy->handle] = this;
	Listen(WindowEvent::Type::Paint, [&](WindowEvent) {
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
	Push(WindowEvent(Type::Update));
	while(impl->legacy->ProcessEvent());
}

void Window::Kill() {
	Impl::map.erase(Impl::map.find(impl->legacy->handle));
	delete impl->legacy;
	impl->alive = false;
}

void Window::Show() {
	impl->legacy->SetShowState(Legacy::Window::ShowState::Showdefault);
}

RectRange Window::ClientRect() {
	impl->legacy->UpdateInfo();
	return impl->legacy->info.clientRect;
}

void Window::Repaint() {
	impl->legacy->Invalidate();
}
