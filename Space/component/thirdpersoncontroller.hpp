#pragma once

#include "../space.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct ThirdPersonController : Component {
		float moveSpeed = .01f;
		float rotateSpeed = .001f;
		Coord3D euler{};

		ThirdPersonController(Object &object) : Component(object) {}

		void Update();
	};
}