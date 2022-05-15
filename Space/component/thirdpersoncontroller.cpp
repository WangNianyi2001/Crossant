#include "thirdpersoncontroller.hpp"
#include "camera.hpp"
#include "Crossant/feature/mouse.hpp"
#include "Crossant/feature/keyboard.hpp"

using namespace Crossant::Graphics::Graphics3D;

void ThirdPersonController::Update() {
	Camera *camera = parent.ComponentOf<Camera>();
	if(camera == nullptr)
		return;
	Coord3D eulerDelta = Coord3D{
		Mouse::deltaPosition[1],
		Mouse::deltaPosition[0],
	};
	euler = euler - eulerDelta * rotateSpeed;
	camera->parent.transform.rotation = Quaternion::Euler(euler);
	using Key = Keyboard::Key;
	Coord3D camMovement = camera->parent.transform.rotation * Coord3D{
		(float)Keyboard::Pressed(Key::D) - (float)Keyboard::Pressed(Key::A),
		(float)Keyboard::Pressed(Key::E) - (float)Keyboard::Pressed(Key::Q),
		(float)Keyboard::Pressed(Key::S) - (float)Keyboard::Pressed(Key::W),
	};
	camera->parent.transform.translation = camera->parent.transform.translation + camMovement * moveSpeed;
}