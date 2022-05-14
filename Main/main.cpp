#include "Crossant/feature/window.hpp"
#include "Crossant/feature/graphics/3d/space/space.hpp"
#include "Crossant/feature/graphics/3d/space/component/meshrenderer.hpp"
#include "Crossant/feature/graphics/3d/space/component/camera.hpp"

using namespace Crossant;
using namespace Crossant::Graphics::Graphics3D;

int Crossant::Main() {
	Window window;

	using WE = Window::Event;
	using EventType = WE::Type;

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

	window.Listen(EventType::Resize, [&](WE event) {
		target.Resize(window.ClientRect().Diagonal());
	});
	window.Listen(EventType::Draw, [&](WE) {
		space.Clear(Context::AttributeMask::ColorBuffer);
		space.Clear(Context::AttributeMask::DepthBuffer);

		camera.Render();

		space.Finish();
		target.DrawOn(window.graphicsTarget);
	});
	window.Listen(EventType::Update, [&](WE e) {
		bool down = Mouse::Pressed(e.mouseButton);
		window.Repaint();
	});
	window.Listen(EventType::MouseMove, [&](WE) {
		Coord2D mouse = Mouse::position / window.graphicsTarget.Size();
		mouse = mouse - Coord2D{ .5f, .5f };
		cameraObj.transform.rotation = Quaternion::Euler({
			-mouse[1], mouse[0], 0
		});
	});
	window.Listen(EventType::Close, [&](WE) {
		window.Kill();
	});

	window.Show();
	for(; window.Alive(); window.Live());
	return 0;
}
