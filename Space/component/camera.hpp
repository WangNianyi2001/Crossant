#pragma once

#include "../space.hpp"

namespace Crossant::Space {
	struct Camera : Component {
		float fov = 45;

		Camera(Object &object) : Component(object) {}

		void Render();
	};
}