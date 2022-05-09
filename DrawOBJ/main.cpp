#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	window->Listen(EventType::Close, [=](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
