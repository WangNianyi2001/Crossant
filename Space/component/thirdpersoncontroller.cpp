#include "thirdpersoncontroller.hpp"
#include "camera.hpp"
#include "Crossant/feature/mouse.hpp"
#include "Crossant/feature/keyboard.hpp"

using namespace Crossant::Graphics::Graphics3D;

void ThirdPersonController::Update() {
	Camera *camera = parent.ComponentOf<Camera>();
	if(camera == nullptr)
		return;
	// .Size() needs to be replaced by client rect
	Coord2D size = camera->parent.parent.target.Size();
	Coord2D mousePos = (Mouse::position / size) - Coord2D{ .5f, .5f };
	camera->parent.transform.rotation = Quaternion::Euler({
		-mousePos[1], mousePos[0], 0
	});
	using Key = Keyboard::Key;
	Coord3D camMovement = camera->parent.transform.rotation * Coord3D{
		(float)Keyboard::Pressed(Key::D) - (float)Keyboard::Pressed(Key::A),
		(float)Keyboard::Pressed(Key::E) - (float)Keyboard::Pressed(Key::Q),
		(float)Keyboard::Pressed(Key::S) - (float)Keyboard::Pressed(Key::W),
	};
	camera->parent.transform.translation = camera->parent.transform.translation + camMovement * speed;
}