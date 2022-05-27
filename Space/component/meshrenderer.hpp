#pragma once

#include "renderer.hpp"
#include "meshfilter.hpp"
#include "../mesh.hpp"
#include "Crossant/feature/graphics/3d/texture.hpp"
#include <map>

namespace Crossant::Graphics::Graphics3D {
	struct MeshRenderer : Renderer {
		struct AttributeUsage {
			Vertex::DatumType datumType = Vertex::DatumType::Float;
			bool used = false;
		};

		std::map<Vertex::Attribute, AttributeUsage> attributeUsage{};
		Texture *texture = nullptr;

		MeshRenderer(Object &object);

		virtual void Render() override;
	};
}