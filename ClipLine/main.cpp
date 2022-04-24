#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	using EventType = WindowEvent::Type;

	Application *app = Application::current;

	Window *window = app->CreateWindow();
	GraphicsContext2D *gdiContext = window->MakeGraphicsContext2D();

	window->Listen(EventType::MouseMove, [=](WindowEvent event) {
		gdiContext->Pixel(
			event.mouse.position,
			Color{ 1, 1, 1 }
		);
		window->Repaint();
	});
	window->Listen(EventType::Paint, [=](WindowEvent) {
		gdiContext->Push();
	});
	window->Listen(EventType::Close, [=](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
