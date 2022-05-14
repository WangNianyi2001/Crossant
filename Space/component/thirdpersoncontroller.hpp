#pragma once

#include "../space.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct ThirdPersonController : Component {
		float speed = .01f;

		ThirdPersonController(Object &object) : Component(object) {}

		void Update();
	};
}