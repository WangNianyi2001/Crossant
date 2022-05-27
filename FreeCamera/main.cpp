#pragma once

#include "Crossant/crossant.hpp"
#include "Space/space.hpp"

int Crossant::Main() {
	using namespace Crossant;
	using namespace Crossant::Space;

	Window window;

	using WE = Window::Event;
	using EventType = WE::Type;

	Graphics::Target target({ 100, 100 });
	auto space = Crossant::Space::Space(target);

	Object cameraObj(space);
	Camera camera(cameraObj);
	FreeCameraController controller(cameraObj);
	cameraObj.transform.translation = { 0, 0, 4 };

	Object cube(space);
	MeshRenderer renderer(cube);

	Mesh cubeMesh = Mesh::cube;
	for(Graphics::Graphics3D::Vertex &vertex : cubeMesh.vertices) {
		vertex.color = (Vector<Float, 4>)vertex.position;
		vertex.texCoord = vertex.position;
	}
	renderer.mesh = &cubeMesh;
	renderer.attributeUsage[Vertex::Attribute::Color].used = true;
	renderer.attributeUsage[Vertex::Attribute::TexCoord].used = true;

	window.Listen(EventType::Resize, [&](WE event) {
		target.Resize(window.graphicsTarget.Size());
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