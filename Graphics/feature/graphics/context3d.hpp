#pragma once

#include "context.hpp"

namespace Graphics {
	struct GraphicsContext3D : GraphicsContext {
		struct Impl;
		Impl *impl;

		GraphicsContext3D(Vector2U size);
		virtual ~GraphicsContext3D() override;

		void Resize(Vector2U size) override;
		void SetPerspective(float perspective);
	};
}
