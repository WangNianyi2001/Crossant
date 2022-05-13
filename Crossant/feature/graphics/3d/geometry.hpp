#pragma once

#include "Crossant/common/type.hpp"
#include <map>
#include <vector>

namespace Crossant::Graphics::Graphics3D {
	struct Vertex {
		enum struct DatumType : Byte {
			Byte, UnsignedByte,
			Short, UnsignedShort,
			Int, UnsignedInt,
			Float, Double,
			Byte2, Byte3, Byte4,
		};
		enum struct Attribute : Byte {
			Vertex,
			Color,
			TexCoord,
			Normal,
			EdgeFlag,
		};

		Coord3D vertex;
		Color color;
		Coord2D texCoord;
		Coord3D normal;
		bool edgeFlag;

		static std::map<Attribute, unsigned> offsetMap;
		static std::map<Attribute, unsigned> dimensionMap;
		static std::map<Attribute, DatumType> typeMap;
	};

	struct Mesh {
		constexpr static Byte TriangleVertexCount = 3;
		using VertexIndex = unsigned;
		using IndexedTriangle = Crossant::Vector<VertexIndex, TriangleVertexCount>;

		static Mesh cube;

		std::vector<Vertex> vertices;
		std::vector<IndexedTriangle> indices;

		Mesh() = default;
		Mesh(std::vector<Vertex> const &vertices, std::vector<IndexedTriangle> const &indices) :
			vertices(vertices), indices(indices) {}
	};
}
