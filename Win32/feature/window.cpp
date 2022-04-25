#include "../win32.hpp"
#include "window.hpp"
#include "application.hpp"

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
			GET_X_LPARAM(legacy.l),
			GET_Y_LPARAM(legacy.l),
	}
	};
	return event;
}

WindowEvent resizeEvent(Event legacy) {
	Graphics::Vector2U size{
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
	{ WM_PAINT, &directEvent<Type::Graph> },
};

Window::Window(Application *application) {
	auto windowClass = application->impl->windowClass;
	impl = new Impl{
		.legacy = new Legacy::Window(
			Legacy::Window::CreationArguments{
				.windowClass = windowClass,
				.instance = windowClass->info.instance,
			}
		),
		.alive = true
	};
	Impl::map[impl->legacy->handle] = this;
	gc2 = new GraphicsContext2D(ClientRect().Diagonal());
	Listen(WindowEvent::Type::Resize, [this](WindowEvent event) {
		gc2->Resize(event.clientSize);
	});
	Listen(WindowEvent::Type::Graph, [this](WindowEvent) {
		Legacy::PaintStruct paintStruct;
		impl->legacy->BeginPaint(&paintStruct);
		Legacy::DeviceContext *targetDC = paintStruct.GetDC();
		Legacy::Bitmap *bitmap = gc2->impl->bitmap;
		BitBlt(
			targetDC->GetHandle<HDC>(),
			0, 0,
			bitmap->size[0], bitmap->size[1],
			bitmap->dc->GetHandle<HDC>(),
			0, 0,
			SRCCOPY
		);
		delete targetDC;
		impl->legacy->EndPaint(&paintStruct);
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

ScreenRect Window::ClientRect() {
	impl->legacy->UpdateInfo();
	return impl->legacy->info.clientRect;
}

void Window::Repaint() {
	impl->legacy->UpdateClient();
}
