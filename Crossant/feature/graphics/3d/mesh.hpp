#pragma once

#include "geometry.hpp"
#include <vector>

namespace Crossant::Graphics::Graphics3D {
	struct Mesh {
		constexpr static Byte TriangleVertexCount = 3;
		using VertexIndex = unsigned;
		using IndexedTriangle = Crossant::Vector<VertexIndex, TriangleVertexCount>;

		virtual Vertex const *VertexHead() const = 0;
		virtual VertexIndex const *IndexHead() const = 0;
		virtual unsigned IndexCount() const = 0;
	};

	struct StaticMesh : Mesh {
		std::vector<Vertex> vertices;
		std::vector<IndexedTriangle> indices;

		virtual Vertex const *VertexHead() const override {
			return &vertices[0];
		}

		virtual VertexIndex const *IndexHead() const override {
			return (VertexIndex *)&indices[0];
		}

		virtual unsigned IndexCount() const override {
			return indices.size();
		}
	};
}