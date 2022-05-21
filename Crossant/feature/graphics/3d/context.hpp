#pragma once

#include "Crossant/common/quaternion.hpp"
#include "Crossant/common/range.hpp"
#include "../context.hpp"
#include "vertex.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Context : Graphics::Context {
		struct Impl;
		Impl *impl;

		Context(Graphics::Target &target);
		virtual ~Context();

		virtual void MakeCurrent() const override;
		void OnResize() override;

		// Basic
		void Render();
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
		void Clear(AttributeMask attribute);

		// Matrix
		void PopMatrix();
		void PushMatrix();
		enum struct MatrixMode : Byte {
			Projection,
			Space,
			Texture
		};
		void SetMatrixMode(MatrixMode mode);
		void LoadIdentity();

		// Transform
		void Translate(Coord3D const &translation);
		void Rotate(Float angle, Coord3D const &axis);
		void Rotate(Quaternion const &quaternion);
		void Scale(Coord3D const &scalor);

		// Viewport
		void Perspective(Float fov, Float aspect, Float near, Float far);

		// Data
		void SetAttributeArray(
			Vertex::Attribute attibute,
			Vertex::DatumType datum,
			bool enabled, void const *data
		);

		// Geometry
		enum struct GeometryType : Byte {
			Points,
			Lines, LineStrip, LineLoop,
			Triangles, TriangleStrip, TriangleFan,
			Quads, QuadStrip, Polygon
		};
		void DrawElements(GeometryType type, std::vector<unsigned> &indices);
		enum struct FaceType : Byte {
			Front, Back, Both
		};
		enum struct FaceMode : Byte {
			Point, Line, Fill
		};
		void PolygonMode(FaceType type, FaceMode mode);
	};
}
