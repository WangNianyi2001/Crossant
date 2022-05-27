#pragma once

#include "renderer.hpp"
#include "Space/common/mesh.hpp"
#include <map>

namespace Crossant::Space {
	struct MeshRenderer : Renderer {
		struct AttributeUsage {
			Vertex::DatumType datumType = Vertex::DatumType::Float;
			bool used = false;
		};

		std::map<Vertex::Attribute, AttributeUsage> attributeUsage{};

		Mesh *mesh;

		MeshRenderer(Object &object);

		virtual void Render() override;
	};
}