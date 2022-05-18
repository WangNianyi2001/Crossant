#pragma once

#include "../space.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Renderer : Component {
		Renderer(Object &object) : Component(object) {}

		virtual void Render() = 0;
	};
}