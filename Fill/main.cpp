#include "Graphics/win32/application.hpp"
#include "Graphics/win32/drawingcontext/gdi.hpp"

using namespace Graphics;

int Application::Main() {
	Application *app = Application::current;
	Win32::Window *window = (Win32::Window *)app->CreateWindow();
	Win32::GDIContext *context = new Win32::GDIContext(window);

	context->Configure([=]() {
		context->Line();
	});

	window->Listen(WindowEventType::Paint, [=](WindowEvent) {
		context->Draw();
	});
	window->Listen(WindowEventType::Close, [=](WindowEvent) {
		window->Destroy();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
