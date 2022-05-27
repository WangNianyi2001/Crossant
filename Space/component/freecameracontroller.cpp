#include "freecameracontroller.hpp"
#include "camera.hpp"
#include "Crossant/mouse.hpp"
#include "Crossant/keyboard.hpp"

using namespace Crossant::Space;

void FreeCameraController::Update() {
	Camera *camera = object.ComponentOf<Camera>();
	if(camera == nullptr)
		return;
	Object &cameraObj = camera->object;
	Coord3D eulerDelta = Coord3D{
		Mouse::deltaPosition[1],
		Mouse::deltaPosition[0],
	};
	euler = euler - eulerDelta * rotateSpeed;
	cameraObj.transform.rotation = Quaternion::Euler(euler);
	using Key = Keyboard::Key;
	Coord3D camMovement = cameraObj.transform.rotation * Coord3D{
		(float)Keyboard::Pressed(Key::D) - (float)Keyboard::Pressed(Key::A),
		(float)Keyboard::Pressed(Key::E) - (float)Keyboard::Pressed(Key::Q),
		(float)Keyboard::Pressed(Key::S) - (float)Keyboard::Pressed(Key::W),
	};
	cameraObj.transform.translation = cameraObj.transform.translation + camMovement * moveSpeed;
}