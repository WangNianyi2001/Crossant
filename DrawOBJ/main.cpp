#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	auto gc = GraphicsContext3D(window->graphicsTarget);

	window->Listen(EventType::Graph, [&](WindowEvent) {
		gc.MakeCurrent();
		gc.LoadIdentity();
		
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
