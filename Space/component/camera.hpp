#pragma once

#include "../space.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Camera : Component {
		float fov = 45;

		Camera(Object &object) : Component(object) {}

		void Render();
	};
}