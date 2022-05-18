#pragma once

#include "renderer.hpp"
#include "meshfilter.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct MeshRenderer : Renderer {
		std::map<Vertex::Attribute, bool> use{};

		MeshRenderer(Object &object);

		virtual void Render() override;
	};
}