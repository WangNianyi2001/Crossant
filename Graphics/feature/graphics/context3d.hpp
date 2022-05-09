#pragma once

#include "context.hpp"

namespace Graphics {
	struct GraphicsContext3D : GraphicsContext {
		struct Impl;
		Impl *impl;

		GraphicsContext3D(GraphicsTarget &target);
		virtual ~GraphicsContext3D() override;

		virtual void MakeCurrent() const override;
		void Resize(Size2D size) override;

		// Basic matrix
		enum struct MatrixMode : Byte {
			Projection,
			Space,
			Texture
		};
		void SetMatrixMode(MatrixMode mode);
		void LoadIdentity();

		// Transform
		void Translate(Coord3D translation);
		void Rotate(Float angle, Coord3D axis);
		void Scale(Coord3D scalor);

		// Projection
		void SetPerspective(Float perspective);
	};
}
