#include "Crossant/3d.hpp"

using namespace Crossant;
using namespace Crossant::Graphics::Graphics3D;

int Crossant::Main() {
	Window *window = Application::current->CreateWindow();

	using EventType = WindowEvent::Type;

	Graphics::Target target;
	auto space = Space(target);
	space.MakeCurrent();
	space.SetPerspective(45);

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
		space.Clear({ Context::AttributeMask::ColorBuffer, Context::AttributeMask::DepthBuffer });
		space.LoadIdentity();
		space.Translate({ 0, 0, -4 });
		space.Rotate(rot, { 1, 1, 1 });

		space.PolygonMode(Context::FaceType::Both, Context::FaceMode::Line);
		cube.Draw(space);

		space.Finish();
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
