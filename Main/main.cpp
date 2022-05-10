#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	using GC3 = GraphicsContext3D;
	GraphicsTarget target({ 1, 1 });
	auto gc3 = GC3(target);
	gc3.MakeCurrent();
	gc3.SetPerspective(45);

	window->Listen(EventType::Resize, [&](WindowEvent event) {
		target.Resize(event.clientSize);
	});
	window->Listen(EventType::Paint, [&](WindowEvent) {
		gc3.Clear({ GC3::AttributeMask::ColorBuffer, GC3::AttributeMask::DepthBuffer });
		gc3.LoadIdentity();
		gc3.Translate({ 0, 0, -4 });
		gc3.Begin(GC3::GeometryType::Triangles);
		gc3.Color({ 1, 1, 1 });
		gc3.Vertex({ 0, 0, 0 });
		gc3.Vertex({ 1, 0, 0 });
		gc3.Vertex({ 1, 1, 0 });
		gc3.End();
		gc3.Finish();
		target.DrawOn(window->graphicsTarget);
	});
	window->Listen(EventType::Update, [&](WindowEvent) {
		window->Repaint();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
