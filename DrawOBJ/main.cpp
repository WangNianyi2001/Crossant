#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	auto gc = GraphicsContext2D(window->graphicsTarget);

	window->Listen(EventType::Graph, [=](WindowEvent) {
		gc.brush->Push(new SolidBrush(Color{ 1, 0, 0 }));
		gc.Rectangle({ {10, 10}, {40, 40} });
	});
	window->Listen(EventType::Close, [=](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
