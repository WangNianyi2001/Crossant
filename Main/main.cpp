#include "Crossant/3d.hpp"

using namespace Crossant;
using namespace Crossant::Graphics::Graphics3D;

int Crossant::Main() {
	Window *window = Application::current->CreateWindow();

	using EventType = WindowEvent::Type;

	using GC3 = Graphics::Graphics3D::Context;
	Graphics::Target target({ 1, 1 });
	auto gc3 = GC3(target);
	gc3.MakeCurrent();
	gc3.SetPerspective(45);

	float rot = 0;

	StaticMesh cube;
	cube.vertices = {
		{ { 0, 0, 0 } },
		{ { 1, 0, 0 } },
		{ { 0, 1, 0 } },
		{ { 1, 1, 0 } },
		{ { 0, 0, 1 } },
		{ { 1, 0, 1 } },
		{ { 0, 1, 1 } },
		{ { 1, 1, 1 } },
	};
	cube.triangles = {
		{ 1, 0, 2 },
		{ 2, 3, 1 },
		{ 0, 4, 6 },
		{ 6, 2, 0 },
		{ 4, 5, 7 },
		{ 7, 6, 4 },
		{ 5, 1, 3 },
		{ 3, 7, 5 },
		{ 6, 7, 3 },
		{ 3, 2, 6 },
		{ 4, 5, 1 },
		{ 1, 0, 4 },
	};

	window->Listen(EventType::Resize, [&](WindowEvent event) {
		target.Resize(event.clientSize);
	});
	window->Listen(EventType::Draw, [&](WindowEvent) {
		gc3.Clear({ GC3::AttributeMask::ColorBuffer, GC3::AttributeMask::DepthBuffer });
		gc3.LoadIdentity();
		gc3.Translate({ 0, 0, -4 });
		gc3.Rotate(rot, { 1, 1, 1 });

		gc3.PolygonMode(GC3::FaceType::Both, GC3::FaceMode::Line);
		cube.Draw(gc3);

		gc3.Finish();
		target.DrawOn(window->graphicsTarget);
	});
	window->Listen(EventType::Update, [&](WindowEvent) {
		rot += .03f;
		window->Repaint();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
