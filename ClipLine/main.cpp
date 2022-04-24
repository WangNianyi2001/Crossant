#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();
	GraphicsContext2D *gc = window->MakeGraphicsContext2D();

	using EventType = WindowEvent::Type;

	window->Listen(EventType::MouseMove, [=](WindowEvent event) {
		gc->Pixel(
			event.mouse.position,
			Color{ 1, 1, 1 }
		);
		window->Repaint();
	});
	window->Listen(EventType::Graph, [=](WindowEvent) {
		gc->Push();
	});
	window->Listen(EventType::Resize, [=](WindowEvent event) {
		gc->Resize(event.clientSize);
	});
	window->Listen(EventType::Close, [=](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
