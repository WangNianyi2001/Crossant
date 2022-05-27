#pragma once

#include "../space.hpp"

namespace Crossant::Space {
	struct Renderer : Component {
		Renderer(Object &object) : Component(object) {}

		virtual void Render() = 0;
	};
}