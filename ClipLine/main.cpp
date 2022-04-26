#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();
	GraphicsContext2D *gc = window->gc2;

	using EventType = WindowEvent::Type;

	window->Listen(EventType::MouseDown, [=](WindowEvent event) {
		ScreenCoord mousePos = event.mouse.position;
		ScreenCoord delta = ScreenCoord{ 50, 50 };
		ScreenRect rect(mousePos - delta, mousePos + delta);
		gc->Rectangle(rect);
		window->Repaint();
	});
	window->Listen(EventType::Graph, [=](WindowEvent) {
		gc->Push();
	});
	window->Listen(EventType::Close, [=](WindowEvent) {
		window->Kill();
	});

	window->Show();
	delete gc->PushPen(new SimplePen(Color{1, 0, 0}));
	delete gc->PushBrush(new SolidBrush(Color{ 1, 1, 0 }));
	for(; window->Alive(); window->Live());
	return 0;
}
