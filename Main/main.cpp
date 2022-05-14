#include "Crossant/feature/window.hpp"
#include "Crossant/feature/graphics/3d/space/space.hpp"
#include "Crossant/feature/graphics/3d/space/component/meshrenderer.hpp"
#include "Crossant/feature/graphics/3d/space/component/camera.hpp"

using namespace Crossant;
using namespace Crossant::Graphics::Graphics3D;

int Crossant::Main() {
	Window window;

	using EventType = WindowEvent::Type;

	Graphics::Target target;
	auto space = Space(target);
	space.MakeCurrent();

	float rot = 0;

	Object cameraObj(space);
	Camera camera(cameraObj);
	cameraObj.transform.translation = { 0, 0, 4 };

	Object cube(space);
	MeshFilter filter(cube);
	MeshRenderer renderer(cube);

	filter.mesh = &Mesh::cube;
	renderer.use[Vertex::Attribute::Color] = true;

	window.Listen(EventType::Resize, [&](WindowEvent event) {
		target.Resize(window.ClientRect().Diagonal());
	});
	window.Listen(EventType::Draw, [&](WindowEvent) {
		space.Clear(Context::AttributeMask::ColorBuffer);
		space.Clear(Context::AttributeMask::DepthBuffer);

		camera.Render();

		space.Finish();
		target.DrawOn(window.graphicsTarget);
	});
	window.Listen(EventType::MouseMove, [&](WindowEvent) {
		Coord2D mouse = window.mouse.position / window.graphicsTarget.Size();
		mouse = mouse - Coord2D{ .5f, .5f };
		cameraObj.transform.rotation = Quaternion::Euler({
			-mouse[1], mouse[0], 0
		});
		window.Repaint();
	});
	window.Listen(EventType::Close, [&](WindowEvent) {
		window.Kill();
	});

	window.Show();
	for(; window.Alive(); window.Live());
	return 0;
}
