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

		using DT = GC3::DataType;
		using DUT = GC3::DatumType;

		gc3.SetDataArrayState(DT::Vertex, true);
		Coord3D vertices[]{
			{ 0, 0, 0 },
			{ 1, 0, 0 },
			{ .5f, .855f, 0 },
		};
		gc3.SetDataArray(DT::Vertex, vertices, 0, DUT::Float, 3);

		gc3.SetDataArrayState(DT::Color, true);
		Color colors[]{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 },
		};
		gc3.SetDataArray(DT::Color, colors, 0, DUT::Float, 3);

		unsigned indices[]{ 0, 1, 2 };

		gc3.DrawElements(GC3::GeometryType::Triangles, 3, indices);

		gc3.Finish();
		target.DrawOn(window->graphicsTarget);
	});
	window->Listen(EventType::Update, [&](WindowEvent) {
		//window->Repaint();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
