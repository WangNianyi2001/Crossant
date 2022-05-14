#pragma once

#include "../space.hpp"
#include "meshfilter.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshRenderer : Component {
		std::map<Vertex::Attribute, bool> use{};

		MeshRenderer(Object &object);

		void Render();
	};
}