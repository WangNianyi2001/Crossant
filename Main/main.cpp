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

	Object cube(space);
	MeshFilter filter(cube);
	MeshRenderer renderer(cube);

	cube.transform.translation = { 0, 0, -4 };
	filter.mesh = &Mesh::cube;
	renderer.useAttributes.color = true;

	window->Listen(EventType::Resize, [&](WindowEvent event) {
		target.Resize(event.clientSize);
	});
	window->Listen(EventType::Draw, [&](WindowEvent) {
		space.Clear({ Context::AttributeMask::ColorBuffer, Context::AttributeMask::DepthBuffer });

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
