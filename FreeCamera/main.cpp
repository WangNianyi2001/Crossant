#pragma once

#include "Crossant/feature/window.hpp"
#include "Space/space.hpp"
#include "Space/component/meshrenderer.hpp"
#include "Space/component/camera.hpp"
#include "Space/component/freecameracontroller.hpp"

int Crossant::Main() {
	using namespace Crossant;
	using namespace Crossant::Graphics::Graphics3D;

	Window window;

	using WE = Window::Event;
	using EventType = WE::Type;

	Graphics::Target target({ 100, 100 });
	auto space = Space(target);

	Object cameraObj(space);
	Camera camera(cameraObj);
	FreeCameraController controller(cameraObj);
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

		space.Render();
		target.DrawOn(window.graphicsTarget);
		});

	window.Listen(EventType::Update, [&](WE e) {
		controller.Update();
		window.Repaint();
		});

	window.Listen(EventType::Close, [&](WE) {
		window.Kill();
		});
	window.SetCursorLockState(true);

	window.Show();
	for(; window.Alive(); window.Live());
	return 0;
}