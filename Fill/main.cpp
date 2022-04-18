#include "Graphics/win32/application.hpp"

int Graphics::Win32::Application::Main() {
	Application *app = Application::current;
	Window::CreationArguments arguments{};
	Window *window = app->CreateWindow(arguments);
	window->Listen(0x0010, [=](Window::Event) {
		window->Quit();
	});
	window->Run();
	return 0;
}
