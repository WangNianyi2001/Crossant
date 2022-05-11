#pragma once

#include "drawable.hpp"
#include "geometry.hpp"
#include <vector>

namespace Crossant::Graphics::Graphics3D {
	struct StaticMesh : Drawable {
		using VertexIndex = unsigned;
		using IndexedTriangle = Crossant::Vector<VertexIndex, 3>;

		std::vector<Vertex> vertices;
		std::vector<IndexedTriangle> triangles;

		virtual void Draw(Context &context) const override {
			context.SetDataArrayState(Context::DataType::Vertex, true);
			context.SetDataArray(
				Context::DataType::Vertex,
				&vertices[0],
				sizeof(Vertex),
				Context::DatumType::Float,
				3
			);
			context.DrawElements(Context::GeometryType::Triangles, triangles.size() * 3, (unsigned *)&triangles[0]);
		}
	};
}