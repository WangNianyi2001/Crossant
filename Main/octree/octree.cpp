#include "Crossant/feature/window.hpp"
#include "Space/space.hpp"
#include "Space/component/camera.hpp"
#include "Space/component/freecameracontroller.hpp"
#include "octree.hpp"
#include <stdio.h>
#include <fstream>

using namespace Crossant;
using namespace Crossant::Graphics::Graphics3D;

int Octree::Main() {
	Window window;

	using WE = Window::Event;
	using EventType = WE::Type;

	Graphics::Target target;
	auto space = Space(target);

	Object cameraObj(space);
	Camera camera(cameraObj);
	FreeCameraController controller(cameraObj);
	cameraObj.transform.translation = { 0, 0, 4 };

	if(argc < 2) {
		puts("No input octree file provided.");
		return 1;
	}
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()) {
		printf("Failed to open file '%S'.\n", argv[1]);
		return 1;
	}
	Octree *octree = Octree::Deserialize(ifs);
	ifs.close();
	octree->Update();
	if(octree == nullptr) {
		puts("Failed to parse octree.");
		return 1;
	}

	Object rendererObj(space);
	OctreeRenderer renderer(rendererObj);
	renderer.Update(octree);

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
