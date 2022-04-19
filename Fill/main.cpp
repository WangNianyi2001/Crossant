#include "Graphics/win32/application.hpp"
#include "Graphics/win32/graphicscontext/gdi.hpp"

using namespace Graphics;

int Application::Main() {
	Application *app = Application::current;
	Window *window = app->CreateWindow();
	Win32::GDIContext gdiContext((Win32::Window *)window);

	gdiContext.Configure([&]() {
		for(int y = 0; y < 20; ++y) {
			for(int x = 0; x < 20; ++x) {
				gdiContext.Pixel(
					Point2F{ (float)x, (float)y },
					Color3B{ 0, 0, 0 }
				);
			}
		}
	});

	window->Listen(WindowEventType::Paint, [&](WindowEvent) {
		gdiContext.Draw();
	});
	window->Listen(WindowEventType::Close, [&](WindowEvent) {
		window->Destroy();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
