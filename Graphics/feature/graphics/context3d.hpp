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

		// Basic
		void Flush();
		void SwapBuffer();
		enum struct AttributeMask : Byte {
			Current,
			Point,
			Line,
			Polygon,
			PolygonStipple,
			PixelMode,
			Lighting,
			Fog,
			DepthBuffer,
			AccumBuffer,
			StencilBuffer,
			Viewport,
			Transform,
			Enable,
			ColorBuffer,
			Hint,
			Eval,
			List,
			Texture,
			Scissor
		};
		void Clear(AttributeMask attributes);

		// Matrix
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

		// Geometry
		enum struct GeometryType : Byte {
			Points,
			Lines, LineStrip, LineLoop,
			Triangles, TriangleStrip, TriangleFan,
			Quads, QuadStrip, Polygon
		};
		void Begin(GeometryType type);
		void End();
		void Vertex(Coord3D coordinate);

		// Appearance
		void Color(Color color);
	};
}
