#pragma once

#include "Crossant/common/basic.hpp"
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
			Position,
			Color,
			TexCoord,
			Normal,
			EdgeFlag,
		};

		Coord3D position;
		Color color;
		Coord2D texCoord;
		Coord3D normal;
		bool edgeFlag;
	};
}
