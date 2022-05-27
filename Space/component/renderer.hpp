#pragma once

#include "Space/common/hierarchy.hpp"

namespace Crossant::Space {
	struct Renderer : Component {
		Renderer(Object &object) : Component(object) {}

		virtual void Render() = 0;
	};
}