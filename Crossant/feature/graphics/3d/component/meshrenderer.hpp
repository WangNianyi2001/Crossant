#pragma once

#include "../space.hpp"
#include "meshfilter.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshRenderer : Component {
		MeshRenderer(Object &object) : Component(object) {}

		void Render() {
			MeshFilter *const filter = object.GetComponentOfType<MeshFilter>();
			if(filter == nullptr || filter->mesh == nullptr)
				return;
			Mesh const *const mesh = filter->mesh;
			Space &space = object.space;
			space.SetMatrixMode(Space::MatrixMode::Space);
			space.LoadIdentity();
			object.transform.Apply();
			space.SetDataArrayState(Context::DataType::Vertex, true);
			space.SetDataArray(
				Context::DataType::Vertex,
				mesh->VertexHead(),
				sizeof(Vertex),
				Context::DatumType::Float,
				Mesh::TriangleVertexCount
			);
			space.DrawElements(
				Context::GeometryType::Triangles,
				mesh->IndexCount() * mesh->TriangleVertexCount,
				mesh->IndexHead()
			);
		}
	};
}