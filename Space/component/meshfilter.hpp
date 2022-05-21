#pragma once

#include "../space.hpp"
#include "../mesh.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshFilter : Component {
		Mesh const *mesh;

		MeshFilter(Object &object, Mesh const *mesh = nullptr) :
			Component(object), mesh(mesh) {}
	};
}