#pragma once

#include "Crossant/feature/window.hpp"
#include "Space/space.hpp"
#include "Space/component/meshrenderer.hpp"
#include "Space/component/camera.hpp"
#include "Space/component/freecameracontroller.hpp"

#include "Crossant/feature/file.hpp"
#include "Crossant/feature/graphics/image.hpp"

int Crossant::Main() {
	File file = File::ChooseFromDisk({
		{ L"Bitmap(*.bmp)", { L"*.bmp" }}
	});
	return 0;

	using namespace Crossant;
	using namespace Crossant::Graphics::Graphics3D;

	File bitmap = File::ChooseFromDisk({
		{ L"Bitmap(*.bmp)", { L"*.bmp" }}
	});
	Graphics::Image *image = Graphics::Image::FromBitmap(bitmap);
	Color pixels[4] = {
		image->At({ 0, 0 }),
		image->At({ 1, 0 }),
		image->At({ 0, 1 }),
		image->At({ 1, 1 }),
	};

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

	Mesh cubeMesh = Mesh::cube;
	for(Vertex &vertex : cubeMesh.vertices)
		vertex.color = (Vector<Float, 4>)vertex.position;
	filter.mesh = &cubeMesh;
	renderer.attributeUsage[Vertex::Attribute::Color].used = true;

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