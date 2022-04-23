#include "Graphics/win32/application.hpp"
#include "Graphics/win32/graphicscontext/gdi.hpp"

using namespace Graphics;

int Application::Main() {
	using EventType = WindowEvent::Type;

	Application *app = Application::current;
	Window *window = app->CreateWindow();
	Win32::GDIContext gdiContext((Win32::Window *)window);

	window->Listen(EventType::MouseDown, [&](WindowEvent event) {
		for(int y = 0; y < 20; ++y) {
			for(int x = 0; x < 20; ++x) {
				gdiContext.Pixel(
					Vector2F{ (float)x, (float)y },
					Color3B{ 255, 0, 0 }
				);
			}
		}
		window->Repaint();
	});
	window->Listen(EventType::Paint, [&](WindowEvent) {
		gdiContext.Push();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Destroy();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
