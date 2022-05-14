#pragma once

#include "../space.hpp"
#include "Crossant/feature/graphics/3d/geometry.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshFilter : Component {
		Mesh const *mesh;

		MeshFilter(Object &object, Mesh const *mesh = nullptr) :
			Component(object), mesh(mesh) {}
	};
}