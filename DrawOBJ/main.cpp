#include "Graphics/graphics.hpp"

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	using GC3 = GraphicsContext3D;
	auto gc = GC3(window->graphicsTarget);
	gc.MakeCurrent();
	gc.SetPerspective(45);
	gc.SetMatrixMode(GC3::MatrixMode::Space);

	window->Listen(EventType::Graph, [&](WindowEvent) {
		gc.Clear({ GC3::AttributeMask::ColorBuffer, GC3::AttributeMask::DepthBuffer });
		gc.LoadIdentity();
		gc.Translate({ 0, 0, 10 });
		gc.Begin(GC3::GeometryType::Triangles);
		gc.Vertex({ 0, 0, 0 });
		gc.Vertex({ 4, 0, 0 });
		gc.Vertex({ 4, 4, 0 });
		gc.Color({ .5f, 0, .5f });
		gc.End();
		gc.Finish();
		window->Validate();
	});
	window->Listen(EventType::Graph, [&](WindowEvent) {
		//window->Invalidate();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
