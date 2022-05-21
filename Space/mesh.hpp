#pragma once
#pragma once

#include "Crossant/common/basic.hpp"
#include "Crossant/feature/graphics/3d/vertex.hpp"
#include <map>

namespace Crossant::Graphics::Graphics3D {
	struct Mesh {
		constexpr static Byte TriangleVertexCount = 3;
		using VertexIndex = unsigned;
		using IndexedTriangle = Crossant::Vector<VertexIndex, TriangleVertexCount>;

		static Mesh cube;

		std::vector<Vertex> vertices;
		std::vector<IndexedTriangle> indices;

		Mesh() = default;
		Mesh(std::vector<Vertex> const &vertices, std::vector<IndexedTriangle> const &indices) :
			vertices(vertices), indices(indices) {}
	};
}
