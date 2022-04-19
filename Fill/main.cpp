#include "Graphics/win32/application.hpp"

using namespace Graphics;

int Application::Main() {
	Application *app = Application::current;
	Window *window = app->CreateWindow();
	window->Listen(WindowEventType::Close, [=](WindowEvent) {
		window->Destroy();
	});
	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
