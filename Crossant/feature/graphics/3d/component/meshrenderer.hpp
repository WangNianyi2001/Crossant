#pragma once

#include "../space.hpp"
#include "meshfilter.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshRenderer : Component {
		struct UseAttributes {
			bool color = false;
			bool texCoord = false;
			bool normal = false;
			bool edgeFlag = false;
		} useAttributes;

		MeshRenderer(Object &object) : Component(object) {}

		void Render() {
			MeshFilter *const filter = object.GetComponentOfType<MeshFilter>();
			if(filter == nullptr || filter->mesh == nullptr)
				return;
			Mesh const *const mesh = filter->mesh;
			Space &space = object.space;
			space.SetMatrixMode(Space::MatrixMode::Space);
			// TODO: Push matrix
			space.LoadIdentity();
			object.transform.Apply();
			// Set pointer of data arrays
			space.SetDataArrayState(Context::DataType::Vertex, true);
			space.SetDataArray(
				Context::DataType::Vertex,
				mesh->VertexHead(),
				sizeof(Vertex),
				Context::DatumType::Float,
				3
			);
			space.SetDataArrayState(Context::DataType::Color, useAttributes.color);
			if(useAttributes.color) {
				space.SetDataArray(
					Context::DataType::Color,
					&mesh->VertexHead()->color,
					sizeof(Vertex),
					Context::DatumType::Float,
					3
				);
			}
			space.SetDataArrayState(Context::DataType::TexCoord, useAttributes.texCoord);
			if(useAttributes.texCoord) {
				space.SetDataArray(
					Context::DataType::TexCoord,
					&mesh->VertexHead()->texCoord,
					sizeof(Vertex),
					Context::DatumType::Float,
					2
				);
			}
			space.SetDataArrayState(Context::DataType::Normal, useAttributes.normal);
			if(useAttributes.normal) {
				space.SetDataArray(
					Context::DataType::Normal,
					&mesh->VertexHead()->normal,
					sizeof(Vertex)
				);
			}
			space.SetDataArrayState(Context::DataType::EdgeFlag, useAttributes.edgeFlag);
			if(useAttributes.edgeFlag) {
				space.SetDataArray(
					Context::DataType::EdgeFlag,
					&mesh->VertexHead()->edgeFlag,
					sizeof(Vertex)
				);
			}
			// Draw
			space.DrawElements(
				Context::GeometryType::Triangles,
				mesh->IndexCount() * mesh->TriangleVertexCount,
				mesh->IndexHead()
			);
			// TODO: Pop matrix
		}
	};
}