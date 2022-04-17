#include "Graphics/win32/window.hpp"

int Graphics::Win32::Main() {
	Window *window = Window::Create();
	window->Listen(16, [=](WindowEvent event) {
		window->Stop();
	});
	window->Run();
	return 0;
}
