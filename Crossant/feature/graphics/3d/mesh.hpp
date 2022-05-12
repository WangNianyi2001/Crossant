#pragma once

#include "geometry.hpp"
#include <vector>

namespace Crossant::Graphics::Graphics3D {
	struct Mesh {
		virtual Vertex const *FirstVertex() const = 0;
	};

	struct StaticMesh : Mesh {
		constexpr static Byte TriangleVertexCount = 3;
		using VertexIndex = unsigned;
		using IndexedTriangle = Crossant::Vector<VertexIndex, TriangleVertexCount>;

		std::vector<Vertex> vertices;
		std::vector<IndexedTriangle> triangles;

		virtual Vertex const *FirstVertex() const override {
			return &vertices[0];
		}

		virtual void Draw(Context &context) const {
			context.SetDataArrayState(Context::DataType::Vertex, true);
			context.SetDataArray(
				Context::DataType::Vertex,
				FirstVertex(),
				sizeof(Vertex),
				Context::DatumType::Float,
				TriangleVertexCount
			);
			context.DrawElements(
				Context::GeometryType::Triangles,
				(unsigned)triangles.size() * TriangleVertexCount,
				(unsigned *)&triangles[0]
			);
		}
	};
}