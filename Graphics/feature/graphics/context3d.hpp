#pragma once

#include "context.hpp"

namespace Graphics {
	struct GraphicsContext3D : GraphicsContext {
		struct Impl;
		Impl *impl;

		GraphicsContext3D(GraphicsTarget &target);
		virtual ~GraphicsContext3D() override;

		virtual void MakeCurrent() const override;
		void Resize(Vector2U size) override;

		void SetPerspective(float perspective);
	};
}
