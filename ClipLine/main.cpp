#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	using EventType = WindowEvent::Type;

	Application *app = Application::current;
	Window *window = app->CreateWindow();
	GraphicsContext2D *gdiContext = window->MakeGraphicsContext2D();

	window->Listen(EventType::MouseDown, [=](WindowEvent event) {
		for(int y = 0; y < 20; ++y) {
			for(int x = 0; x < 20; ++x) {
				gdiContext->Pixel(
					Vector2F{ (float)x, (float)y },
					Color(1, 1, 1)
				);
			}
		}
		window->Repaint();
	});
	window->Listen(EventType::MouseMove, [=](WindowEvent event) {
		gdiContext->Pixel(
			event.mouse.position.Convert<float>(),
			Color(1, 1, 1)
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
