#pragma once

#include "Crossant/common/type.hpp"

namespace Crossant::Graphics::Graphics3D {
	struct Vertex {
		Coord3D position;
		Color color;
		Coord2D texCoord;
		Coord3D normal;
		bool edgeFlag;
	};
}
