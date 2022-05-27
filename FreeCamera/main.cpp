#pragma once

#include "Crossant/feature/window.hpp"
#include "Space/space.hpp"
#include "Space/component/meshrenderer.hpp"
#include "Space/component/camera.hpp"
#include "Space/component/freecameracontroller.hpp"

#include "Crossant/crossant.hpp"
#include "Crossant/feature/graphics/image.hpp"
#include "Crossant/feature/graphics/3d/texture.hpp"

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
	std::ifstream bitmap(ChooseFile({
		{ L"Bitmap(*.bmp)", { L"*.bmp" }}
	}));
	Graphics::Image *image = Graphics::Image::FromBitmap(bitmap);
	Texture texture(*image);
	renderer.texture = &texture;

	Mesh cubeMesh = Mesh::cube;
	for(Vertex &vertex : cubeMesh.vertices) {
		// vertex.color = (Vector<Float, 4>)vertex.position;
		vertex.texCoord = vertex.position;
	}
	filter.mesh = &cubeMesh;
	// renderer.attributeUsage[Vertex::Attribute::Color].used = true;
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