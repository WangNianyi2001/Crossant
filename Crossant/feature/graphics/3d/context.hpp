#pragma once

#include "../context.hpp"
#include <initializer_list>

namespace Crossant::Graphics::Graphics3D {
	struct Context : Graphics::Context {
		struct Impl;
		Impl *impl;

		Context(Graphics::Target &target);
		virtual ~Context() override;

		virtual void MakeCurrent() const override;
		void OnResize() override;

		// Basic
		void Finish();
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
		void Clear(std::initializer_list<AttributeMask> attributes);

		// Matrix
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

		// Projection
		void SetPerspective(Float perspective);

		// Data
		enum struct DatumType : Byte {
			Byte, UnsignedByte,
			Short, UnsignedShort,
			Int, UnsignedInt,
			Float, Double,
			Byte2, Byte3, Byte4,
		};
		enum struct DataType : Byte {
			Color,
			EdgeFlag,
			Normal,
			TexCoord,
			Vertex
		};
		void SetDataArrayState(DataType type, bool enabled);
		void SetDataArray(DataType type, void const* array, unsigned stride = 0, DatumType datumType = DatumType::Float, int dimension = 4);

		// Geometry
		enum struct GeometryType : Byte {
			Points,
			Lines, LineStrip, LineLoop,
			Triangles, TriangleStrip, TriangleFan,
			Quads, QuadStrip, Polygon
		};
		void DrawElements(GeometryType type, unsigned count, unsigned const *indices = nullptr, DatumType datumType = DatumType::UnsignedInt);
		enum struct FaceType : Byte {
			Front, Back, Both
		};
		enum struct FaceMode : Byte {
			Point, Line, Fill
		};
		void PolygonMode(FaceType type, FaceMode mode);
	};
}
