#include "Graphics/graphics.hpp"
#define WIN32_CLEAN_AND_MEAN
#include <Windows.h>
#undef CreateWindow
#include <gl/gl.h>
#include <gl/glu.h>

using namespace Graphics;

int Application::Main() {
	Window *window = current->CreateWindow();

	using EventType = WindowEvent::Type;

	using GC3 = GraphicsContext3D;
	auto gc = GC3(window->graphicsTarget);
	gc.MakeCurrent();
	gc.SetPerspective(45);

	window->Listen(EventType::Paint, [&](WindowEvent) {
		gc.Clear({ GC3::AttributeMask::ColorBuffer, GC3::AttributeMask::DepthBuffer });
		gc.LoadIdentity();
		gc.Translate({ 0, 0, -4 });
		gc.Begin(GC3::GeometryType::Triangles);
		gc.Color({ 1, 1, 1 });
		gc.Vertex({ 0, 0, 0 });
		gc.Vertex({ 1, 0, 0 });
		gc.Vertex({ 1, 1, 0 });
		gc.End();
		gc.Finish();
	});
	window->Listen(EventType::Paint, [&](WindowEvent) {
		window->Repaint();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
