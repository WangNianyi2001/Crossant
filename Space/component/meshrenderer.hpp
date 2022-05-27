#pragma once

#include "renderer.hpp"
#include "meshfilter.hpp"
#include "../mesh.hpp"
#include <map>

namespace Crossant::Space {
	struct MeshRenderer : Renderer {
		struct AttributeUsage {
			Vertex::DatumType datumType = Vertex::DatumType::Float;
			bool used = false;
		};

		std::map<Vertex::Attribute, AttributeUsage> attributeUsage{};

		MeshRenderer(Object &object);

		virtual void Render() override;
	};
}