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

	StaticMesh cubeMesh;
	cubeMesh.vertices = {
		{ { 0, 0, 0 } },
		{ { 1, 0, 0 } },
		{ { 0, 1, 0 } },
		{ { 1, 1, 0 } },
		{ { 0, 0, 1 } },
		{ { 1, 0, 1 } },
		{ { 0, 1, 1 } },
		{ { 1, 1, 1 } },
	};
	cubeMesh.indices = {
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

	Object cube(space);
	MeshFilter filter(cube);
	MeshRenderer renderer(cube);

	filter.mesh = &cubeMesh;
	cube.transform.translation = { 0, 0, -4 };

	window->Listen(EventType::Resize, [&](WindowEvent event) {
		target.Resize(event.clientSize);
	});
	window->Listen(EventType::Draw, [&](WindowEvent) {
		space.Clear({ Context::AttributeMask::ColorBuffer, Context::AttributeMask::DepthBuffer });
		space.PolygonMode(Context::FaceType::Both, Context::FaceMode::Line);

		renderer.Render();

		space.Finish();
		target.DrawOn(window->graphicsTarget);
	});
	window->Listen(EventType::Update, [&](WindowEvent) {
		rot += PI / 3000;
		cube.transform.rotation = Quaternion::AxisAngle({ 1, 1, 1 }, rot);
		window->Repaint();
	});
	window->Listen(EventType::Close, [&](WindowEvent) {
		window->Kill();
	});

	window->Show();
	for(; window->Alive(); window->Live());
	return 0;
}
