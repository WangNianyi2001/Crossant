#include "window.hpp"
#include "application.hpp"
#include "graphics/target.hpp"

using namespace Crossant;

template<Type type>
WindowEvent directEvent(Event) {
	return WindowEvent{ type };
}

template<Type type>
WindowEvent mouseEvent(Event legacy) {
	WindowEvent event{ type };
	event.mouse = Mouse{
		.position = {
			(Float)GET_X_LPARAM(legacy.l),
			(Float)GET_Y_LPARAM(legacy.l),
		}
	};
	return event;
}

WindowEvent resizeEvent(Event legacy) {
	Size2D size{
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
	Push(WindowEvent(Type::Update));
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
